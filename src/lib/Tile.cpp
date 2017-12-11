#include "Tile.hpp"

namespace gol
{

Tile::Tile()
{
    setState(gol::State::None);
}

State Tile::getState() const
{
    return state;
}

void Tile::setState(const State & state)
{
    this->state = state;
}

}
