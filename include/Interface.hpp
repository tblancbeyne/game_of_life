#ifndef GOL_INTERFACE_HPP
#define GOL_INTERFACE_HPP

#include <SFML/Graphics.hpp>

#include "Matrix.hpp"

namespace gol
{

class Interface : public sf::RenderWindow
{
 public:
  Interface(const Matrix & matrix);

  void update();

  void drawMatrix();

  void eventManagement();

  bool isRunning();

 private:
  Matrix matrix;
  void resize(const sf::Event & event);
  void updateState(const sf::Event & event);
  void updateTile(const sf::Event & event);
  sf::Vector2u getTilePosition(const sf::Event & event);
  gol::State state;
  bool buttonPressed;
  bool running;
};

}

#endif // PIC_INTERFACE_HPP
