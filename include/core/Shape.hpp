#pragma once

#include <cstddef>

namespace mlt::core
{
    struct Shape
    {
        size_t rows;
        size_t cols;

        Shape(const size_t rows, size_t cols) : rows(rows), cols(cols) {}

        Shape() : Shape(0, 0) {}
    };
} // namespace mlt::core