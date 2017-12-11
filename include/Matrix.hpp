#ifndef GOL_MATRIX_HPP
#define GOL_MATRIX_HPP

#include <vector>

#include <SFML/Graphics.hpp>

#include "Tile.hpp"

namespace gol
{
    class Matrix
    {
        public:
            Matrix();
            Matrix(std::size_t row_number, std::size_t col_number);

            void reset_tiles();

            Tile& operator[](std::size_t i);
            Tile const& operator[](std::size_t i) const;

            Tile& operator()(std::size_t row, std::size_t col);
            Tile const& operator()(std::size_t row, std::size_t col) const;

            std::size_t row_number() const;
            std::size_t col_number() const;

            void set_square_size(const sf::Vector2u & window_size);
            float get_square_size() const;

        private:
            std::size_t m_row_number;
            std::size_t m_col_number;
            std::vector<Tile> m_data;
            float square_size;
    };

    Tile& get(Matrix& matrix, std::size_t i);

    Tile const& get(Matrix const& matrix, std::size_t i);

    Tile& get(Matrix & matrix, std::size_t i, std::size_t j);

    Tile const& get(Matrix const& matrix, std::size_t i, std::size_t j);

}

#endif // GOL_MATRIX_HPP

