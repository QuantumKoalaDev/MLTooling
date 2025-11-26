#pragma once

#include <cstddef>

struct Shape
{
	size_t rows;
	size_t cols;

	Shape(size_t rows, size_t cols) : rows(rows), cols(cols)
	{}
};