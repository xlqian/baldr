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
   * @param   ptr  Pointer to a bit of memory that has the info for this complex restriction
   */
  ComplexRestriction(char* ptr);

  /**
   * Destructor
   */
  virtual ~ComplexRestriction();

  /**
   * Get the restriction's from id
   * @return  Returns the from id
   */
  uint64_t from_id() const;

  /**
   * Get the restriction's to id
   * @return  Returns the to id
   */
  uint64_t to_id() const;

  /**
   * Get the number of vias.
   * @return  Returns the number of vias
   */
  uint64_t via_count() const;

  /**
   * Get the via id at a index
   * @param  index  Index into the via list.
   * @return  Returns the via
   */
  uint64_t GetViaId(uint8_t index) const;

  /**
   * Get the restriction type
   * @return  Returns the restriction type
   */
  RestrictionType type() const;

  /**
   * Get the modes impacted by the restriction.
   * @return  Returns the access modes
   */
  uint64_t modes() const;

  /**
   * Gets the begin day for this restriction.
   * @return  Returns the begin day
   */
  DOW begin_day() const;

  /**
   * Gets the end day for this restriction.
   * @return  Returns the end day
   */
  DOW end_day() const;

  /**
   * Gets the begin time for this restriction.
   * @return  Returns the begin time in seconds.
   */
  uint64_t begin_time() const;

  /**
   * Gets the end time for this restriction.
   * @return  Returns the end time in seconds.
   */
  uint64_t end_time() const;

  /**
   * Gets the elapsed time for this restriction.
   * @return  Returns the elapsed time in seconds.
   */
  uint64_t elapsed_time() const;

  /**
   * Get a list of vias
   * @return  Returns the list of vias
   */
  const std::vector<uint64_t> GetVias() const;

  struct PackedRestriction {
    uint64_t type_          : 10; // Restriction type
    uint64_t modes_         : 12; // Mode(s) this access restriction applies to
    uint64_t begin_day_     :  3; // Start day of week this access restriction applies
    uint64_t end_day_       :  3; // End day of week this access restriction applies
    uint64_t begin_time_    : 17; // Begin time (seconds from midnight -- 86400 secs per day)
    uint64_t elapsed_time_  : 15; // elapsed time (secs)
    uint64_t via_count_     :  3; // size of via list.
    uint64_t spare_         :  1;
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
