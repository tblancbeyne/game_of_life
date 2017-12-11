#include "Interface.hpp"

#include <iostream>

namespace gol
{

Interface::Interface(const Matrix & matrix) : matrix{matrix}, state{gol::State::None}, buttonPressed{false}, running{false}
{
    this->matrix.reset_tiles();
    this->matrix.set_square_size(sf::Vector2u(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));

    std::size_t width = this->matrix.get_square_size() * this->matrix.col_number();
    std::size_t height = this->matrix.get_square_size() * this->matrix.row_number();

    create(sf::VideoMode(width,height), "Game of Life", sf::Style::Close + sf::Style::Resize);

//    setFramerateLimit(30);
}

void Interface::eventManagement()
{
    sf::Event event;
    while (pollEvent(event))
    {
        // "Close requested" event: we close the window
        if (event.type == sf::Event::Closed)
            close();

        if (event.type == sf::Event::Resized)
        {
            resize(event);
        }

        if (!buttonPressed)
            if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
            {
                running = !running;
            }

        if (!running)
        {
            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
                updateState(event);

            if (event.type == sf::Event::MouseMoved && buttonPressed)
            {
                updateTile(event);
            }
        }
    }
}

void Interface::update()
{
    matrix.update();
}

bool Interface::isRunning()
{
    return running;
}

void Interface::drawMatrix()
{
    float square_size = matrix.get_square_size();

    for (std::size_t i = 0; i < matrix.row_number(); ++i)
        for (std::size_t j = 0; j < matrix.col_number(); ++j)
        {
            sf::RectangleShape square(sf::Vector2f(square_size,square_size));
            square.setOrigin(square_size / 2.0, square_size / 2.0);
            square.setPosition(square_size / 2.0 + square_size*i, square_size / 2.0 + square_size*j);
            square.setOutlineThickness(1);
            if ((matrix(i, j).getState() == State::In))
            {
                square.setFillColor(sf::Color::Black);
                square.setOutlineColor(sf::Color(30,30,30));
            }
            else
            {
                square.setOutlineColor(sf::Color::Black);
                square.setFillColor(sf::Color::White);
            }
            draw(square);
        }
}

void Interface::resize(const sf::Event & event)
{
    sf::View view;
    if (event.size.width > sf::VideoMode::getDesktopMode().width || event.size.height > sf::VideoMode::getDesktopMode().height)
    {
        view = sf::View(sf::FloatRect(0.f, 0.f, sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height));
    }
    else
    {
        view = sf::View(sf::FloatRect(0.f, 0.f, event.size.width, event.size.height));
    }
    setView(view);

    matrix.set_square_size(getSize());
}

void Interface::updateState(const sf::Event & event)
{
    try
    {
        sf::Vector2u tile_position = getTilePosition(event);

        if (event.type == sf::Event::MouseButtonReleased && event.mouseButton.button == sf::Mouse::Left)
        {
            buttonPressed = false;
            return;
        }

        if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
            buttonPressed = true;

        state = matrix(tile_position.x, tile_position.y).getState();
        switch(state)
        {
            case State::In:
                state = State::None;
                break;
            case State::None:
                state = State::In;
                break;
        }

        updateTile(event);
    }
    catch (std::out_of_range) {}
}

void Interface::updateTile(const sf::Event & event)
{
    try
    {
        sf::Vector2u tile_position = getTilePosition(event);

        matrix(tile_position.x, tile_position.y).setState(state);
    }
    catch ( const std::out_of_range e)
    {
        buttonPressed = false;
    }
}

sf::Vector2u Interface::getTilePosition(const sf::Event & event)
{
    sf::Vector2u mouse_position;
    if (event.type == sf::Event::MouseMoved)
        mouse_position = sf::Vector2u(event.mouseMove.x, event.mouseMove.y);
    else if (event.type == sf::Event::MouseButtonPressed)
        mouse_position = sf::Vector2u(event.mouseButton.x, event.mouseButton.y);

    float square_size = matrix.get_square_size();

    // Too low or too right or to high or too left
    if (mouse_position.x > square_size*(matrix.col_number()) || mouse_position.y > square_size*(matrix.row_number()))
        throw std::out_of_range("Not inside the matrix: " + std::to_string(mouse_position.x) + " " + std::to_string(mouse_position.y));

    std::size_t right_extremity = square_size;
    std::size_t tile_col = 0;
    while (right_extremity < mouse_position.x)
    {
        tile_col++;
        right_extremity += square_size;
    }

    std::size_t left_extremity = square_size;
    std::size_t tile_row = 0;
    while (left_extremity < mouse_position.y)
    {
        tile_row++;
        left_extremity += square_size;
    }

    return sf::Vector2u(tile_col, tile_row);

}

}
