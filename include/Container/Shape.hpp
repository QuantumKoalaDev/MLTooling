#pragma once

#include <cstddef>

namespace Container
{
	struct [[deprecated("Use mlt::core::Shape instead")]] Shape
	{
		size_t rows;
		size_t cols;

		Shape(const size_t rows, const size_t cols) : rows(rows), cols(cols)
		{}
	};
}
