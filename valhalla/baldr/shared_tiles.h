#ifndef VALHALLA_BALDR_SHARED_TILES_H_
#define VALHALLA_BALDR_SHARED_TILES_H_

#include <valhalla/midgard/util.h>
#include <valhalla/midgard/sequence.h>
#include <valhalla/baldr/graphid.h>
#include <valhalla/baldr/tilehierarchy.h>

namespace valhalla {
namespace baldr {

// Tile information: pointer to the start of the tile and size of the tile
using tile_pair = std::pair<char*, uint32_t>;

/**
 * Shared tiles. Assumes that all tiles and an index to each are provided
 * in a single file that is memory mapped and shared.
 */
class SharedTiles {
 public:

  static SharedTiles& get_shared_tiles(const boost::property_tree::ptree& pt) {
    // Static instance
    static SharedTiles instance(pt);
    return instance;
  }

  // Delete copy and move constructors and assign operators
  SharedTiles(SharedTiles const&) = delete;             // Copy construct
  SharedTiles(SharedTiles&&) = delete;                  // Move construct
  SharedTiles& operator=(SharedTiles const&) = delete;  // Copy assign
  SharedTiles& operator=(SharedTiles &&) = delete;      // Move assign

  /**
   * Get a pointer to the beginning of the tile within the mmap'd file. Also
   * returns the tile size.
   * @param   graphid  Tile Id.
   * @return  Returns a pair with the pointer to the tile as the first element
   *          and the size of the tile as the second.
   */
  tile_pair GetTile(const GraphId& graphid) const;

  /**
   * Gets a pointer to the tile data (nullptr if not available)
   */
  char* get_tile_ptr() const;

 protected:
  // Maximum hierarchy level
  int max_level_;

  // Number of tiles per level
  uint32_t tile_count_[kMaxGraphHierarchy];

  // Indexes to the start of each tile for each level
  uint64_t* indexes_[kMaxGraphHierarchy];

  // Size of each tile
  uint32_t* sizes_[kMaxGraphHierarchy];

  // Memory mapped tiles
  midgard::mem_map<char> tiles_;

  // Pointer to the memory mapped tile data
  char* tile_ptr_;

  // Private constructor
  SharedTiles();

  /**
   * Constructor
   */
  SharedTiles(const boost::property_tree::ptree& pt);
};

}
}

#endif  // VALHALLA_BALDR_SHARED_TILES_H_
