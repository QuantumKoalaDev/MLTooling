#pragma once

#include "Shape.hpp"

#include <vector>
#include <stddef.h>

namespace Container
{
	class Mat
	{
	private:
		std::vector<float> m_mat;
		Shape m_shape;

	public:
		Mat(size_t rows, size_t cols, std::vector<float> mat);
		~Mat() = default;

		std::vector<float> getRow(size_t rowIndex) const;

		Container::Shape getShape() const;

		void addRow(const std::vector<float>& row);

		float& operator()(size_t row, size_t col);
		const float& operator()(size_t row, size_t col) const;
	};
}
