#pragma once

#include "Shape.hpp"

#include <vector>
#include <cstddef>

namespace Container
{
	class Mat
	{
	private:
		std::vector<float> m_mat;
		Shape m_shape;

	public:
		Mat(size_t rows, size_t cols, float init = 0.f);
		Mat(size_t rows, size_t cols, std::vector<float> mat);
		~Mat() = default;

		[[nodiscard]] std::vector<float> getRow(size_t rowIndex) const;

		[[nodiscard]] Container::Shape getShape() const;

		void addRow(const std::vector<float>& row);

		float& operator()(size_t row, size_t col);
		const float& operator()(size_t row, size_t col) const;

		Mat& operator+=(const Mat& other);
		Mat operator+(const Mat& other) const;
		Mat operator*(const Mat& other) const;
		// *=, +, -
	};
}
