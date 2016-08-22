#include <string.h>
#include <algorithm>
#include "baldr/complexrestriction.h"


namespace valhalla {
namespace baldr {

ComplexRestriction::ComplexRestriction(char* ptr, const bool reverse) {

  from_id_ = *(reinterpret_cast<uint64_t*>(ptr));
  ptr += sizeof(uint64_t);

  to_id_ = *(reinterpret_cast<uint64_t*>(ptr));
  ptr += sizeof(uint64_t);

  restriction_ = reinterpret_cast<PackedRestriction*>(ptr);
  ptr += sizeof(PackedRestriction);

  via_list_ = reinterpret_cast<uint64_t*>(ptr);
  ptr += (via_count() * sizeof(uint64_t));

  restriction_->reverse_ = reverse;
}

ComplexRestriction::~ComplexRestriction() {
  //nothing to delete these are all shallow pointers for the moment held
  //by another object
}

// restriction is from this id
uint64_t ComplexRestriction::from_id() const {
  return from_id_;
}

// restriction is to this id
uint64_t ComplexRestriction::to_id() const {
  return to_id_;
}

// Get the reversed flag
bool ComplexRestriction::is_reversed() const {
  return restriction_->reverse_;
}

// Get the number of vias.
uint64_t ComplexRestriction::via_count() const {
  return restriction_->via_count_;
}

// Get the via based on the index.
uint64_t ComplexRestriction::GetViaId(uint8_t index) const {
  if(index < restriction_->via_count_)
    return via_list_[index];
  else
    throw std::runtime_error("Via Id index was out of bounds");
}

// Get the type
RestrictionType ComplexRestriction::type() const {
  return static_cast<RestrictionType>(restriction_->type_);
}

// Get the modes impacted by the restriction.
uint64_t ComplexRestriction::modes() const {
  return restriction_->modes_;
}

// Gets the begin day for this restriction.
DOW ComplexRestriction::begin_day() const {
  return static_cast<DOW>(restriction_->begin_day_);
}

// Gets the end day for this restriction.
DOW ComplexRestriction::end_day() const {
  return static_cast<DOW>(restriction_->end_day_);
}

// Gets the begin time for this restriction.
uint64_t ComplexRestriction::begin_time() const {
  return restriction_->begin_time_;
}

// Gets the end time for this restriction.
uint64_t ComplexRestriction::end_time() const {
  return restriction_->begin_time_ + restriction_->elapsed_time_;
}

// Gets the elapsed time for this restriction.
uint64_t ComplexRestriction::elapsed_time() const {
  return restriction_->elapsed_time_;
}

// Get a list of vias
const std::vector<uint64_t> ComplexRestriction::GetVias() const {
  // Get each via
  std::vector<uint64_t> vias;
  for (uint32_t i = 0; i < via_count(); i++) {
    uint64_t id = GetViaId(i);

    if (i < kMaxViasPerRestriction) {
      vias.push_back(id);
    } else {
      throw std::runtime_error("GetVias: count exceeds max via amount per restriction.");
    }
  }
  if (is_reversed())
    std::reverse(vias.begin(), vias.end());
  return vias;
}

// overloaded == operator - used to ensure no dups in tiles.
bool ComplexRestriction::operator == (const ComplexRestriction& other) const {

  if (from_id() != other.from_id() || to_id() != other.to_id() ||
      GetVias() != other.GetVias() || type() != other.type() ||
      modes() != other.modes() || begin_day() != other.begin_day() ||
      end_day() != other.end_day() || begin_time() != other.begin_time() ||
      elapsed_time() != other.elapsed_time())
    return false;

  return true;
}

}
}
