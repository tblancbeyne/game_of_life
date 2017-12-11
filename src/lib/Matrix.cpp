#include "Matrix.hpp"

#include <iostream>
#include <cassert>

namespace gol
{

Matrix::Matrix(std::size_t row_number, std::size_t col_number) :
    m_row_number(row_number), m_col_number(col_number)
{
    for (std::size_t i = 0; i < row_number; ++i)
        for (std::size_t j = 0; j < col_number; ++j)
            m_data.push_back(Tile());

}

Matrix::Matrix() : Matrix(0, 0)
{
}

void Matrix::reset_tiles()
{
    for(std::size_t i = 0; i < col_number(); ++i)
        for(std::size_t j = 0; j < row_number(); ++j)
            operator()(i, j).setState(State::None);
}

void Matrix::update()
{
    gol::Matrix tmp(row_number(), col_number());

    for (std::size_t i = 0; i < row_number(); ++i)
        for (std::size_t j = 0; j < col_number(); ++j)
        {
            std::size_t count = 0;
            for (int k = -1; k <= 1; ++k)
                for (int l = -1; l <= 1; ++l)
                    if (k != 0 || l != 0)
                        if (i + k > 0 && i + k < row_number() && j + l > 0 && j + l < col_number())
                            if (operator()(i + k, j + l).getState() == gol::State::In)
                                ++count;

            if (count == 3)
            {
                tmp(i,j).setState(gol::State::In);
            }
            else if (count > 3)
            {
                tmp(i,j).setState(gol::State::None);
            }
            else if (count == 2)
            {
                tmp(i,j).setState(operator()(i,j).getState());
            }
            else if (count < 2)
            {
                tmp(i,j).setState(gol::State::None);
            }
        }

    for (std::size_t i = 0; i < row_number(); ++i)
        for (std::size_t j = 0; j < col_number(); ++j)
        {
            operator()(i,j).setState(tmp(i,j).getState());
        }
}

Tile const& Matrix::operator[](std::size_t i) const
{
    assert(i >= 0 && i < m_row_number * m_col_number);
    return m_data[i];
}

Tile& Matrix::operator[](std::size_t i)
{
    return const_cast<Tile&>(static_cast<const Matrix*>(this)->operator[](i));
}

Tile const& Matrix::operator()(std::size_t row, std::size_t col) const
{
    assert(row >= 0 && row < m_row_number);
    assert(col >= 0 && col < m_col_number);
    return m_data[row * m_col_number + col];
}

Tile& Matrix::operator()(std::size_t row, std::size_t col)
{
    return const_cast<Tile&>(static_cast<const Matrix*>(this)->operator()(row, col));
}

std::size_t Matrix::row_number() const
{
    return m_row_number;
}

std::size_t Matrix::col_number() const
{
    return m_col_number;
}

Tile& get(Matrix& matrix, std::size_t i)
{
    return matrix[i];
}

Tile const& get(Matrix const& matrix, std::size_t i)
{
    return matrix[i];
}

Tile& get(Matrix& matrix, std::size_t i, std::size_t j)
{
    return matrix(i, j);
}

Tile const& get(Matrix const& matrix, std::size_t i, std::size_t j)
{
    return matrix(i, j);
}

void Matrix::set_square_size(const sf::Vector2u & window_size)
{
    square_size = 0;

    std::size_t min_width = window_size.x / (col_number());
    std::size_t min_height = window_size.y / (row_number());

    if (min_width > min_height)
    {
        square_size = min_height;
    }
    else
    {
        square_size = min_width;
    }
}

float Matrix::get_square_size() const
{
    return square_size;
}

}
