#pragma once

#include "Shape.hpp"

#include <vector>

namespace Container
{
	class Mat
	{
	private:
		std::vector<std::vector<float>> m_mat;

	public:
		Mat();
		Mat(std::vector<std::vector<float>>& mat);
		~Mat() = default;

		std::vector<float> getRow(size_t rowIndex) const;

		Container::Shape getShape() const;

		void addRow(const std::vector<float>& row);
	};
}
