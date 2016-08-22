#ifndef VALHALLA_BALDR_COMPLEXRESTRICTION_H_
#define VALHALLA_BALDR_COMPLEXRESTRICTION_H_

#include <vector>
#include <string>
#include <ostream>
#include <iostream>

#include <valhalla/midgard/util.h>
#include <valhalla/baldr/graphid.h>
#include <valhalla/baldr/json.h>
#include <valhalla/baldr/graphconstants.h>

using namespace valhalla::midgard;

namespace valhalla {
namespace baldr {

constexpr size_t kMaxViasPerRestriction = 8;


/**
 * Information held for each complex access restriction.
 */
class ComplexRestriction {
 public:
  ComplexRestriction() = delete;

  /**
   * Constructor
   * @param  ptr  Pointer to a bit of memory that has the info for this complex restriction
   */
  ComplexRestriction(char* ptr, const bool reverse = false);

  /**
   * Destructor
   */
  virtual ~ComplexRestriction();

  // restriction is from this id
  uint64_t from_id() const;

  // restriction is to this id
  uint64_t to_id() const;

  // Get the reversed flag
  bool is_reversed() const;

  // Get the number of vias.
  uint64_t via_count() const;

  // Get the via based on the index.
  uint64_t GetViaId(uint8_t index) const;

  // Get the type
  RestrictionType type() const;

  // Get the modes impacted by the restriction.
  uint64_t modes() const;

  // Get the begin day for this restriction.
  DOW begin_day() const;

  // Get the end day for this restriction.
  DOW end_day() const;

  // Gets the begin time for this restriction.
  uint64_t begin_time() const;

  // Gets the end time for this restriction.
  uint64_t end_time() const;

  // Gets the elapsed time for this restriction.
  uint64_t elapsed_time() const;

  // Get a list of names
  const std::vector<uint64_t> GetVias() const;

  bool operator == (const ComplexRestriction& other) const;

  struct PackedRestriction {
    uint64_t type_          : 10; // Restriction type
    uint64_t modes_         : 12; // Mode(s) this access restriction applies to
    uint64_t begin_day_     :  3; // Start day of week this access restriction applies
    uint64_t end_day_       :  3; // End day of week this access restriction applies
    uint64_t begin_time_    : 17; // Begin time (seconds from midnight -- 86400 secs per day)
    uint64_t elapsed_time_  : 15; // elapsed time (secs)
    uint64_t reverse_       :  1; // should we reverse the vias?
    uint64_t via_count_     :  3; // size of via list.
  };

 protected:

  uint64_t from_id_;              // from edge id
  uint64_t to_id_;                // to edge id

  // Where we keep most of the static data
  PackedRestriction* restriction_;

  // List of vias
  uint64_t* via_list_;             // via edge ids

};

}
}

#endif  // VALHALLA_BALDR_COMPLEXRESTRICTION_H_
