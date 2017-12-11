#ifndef GOL_TILE_HPP
#define GOL_TILE_HPP
#endif // PIC_TILE_HPP

#include <cstdlib>

namespace gol
{

// Enumeration of two possible states
enum class State { None, In };

class Tile
{
 public:
  Tile();

  gol::State getState() const;

  void setState(const State & state);

  void operator++();

 private:
  State state;
  std::size_t age;

};

}

