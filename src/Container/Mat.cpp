#include "../include/Container/Mat.hpp"

#include <stdexcept>

using namespace Container;


Mat::Mat(size_t rows, size_t cols, std::vector<float> mat): m_mat(std::move(mat)), m_shape(Shape(rows, cols))
{}

std::vector<float> Mat::getRow(size_t rowIndex) const
{
	if (rowIndex >= m_shape.rows)
		throw new std::invalid_argument("Row index out of bound");

	std::vector<float> row;
	row.resize(m_shape.cols);

	const size_t matRowPos = rowIndex * m_shape.cols;

	for (int colNumber{ 0 }; colNumber < m_shape.cols; colNumber++)
	{
		row[colNumber] = m_mat[matRowPos + colNumber];
	}

	return row;
}

Shape Mat::getShape() const
{
	return m_shape;
}

void Mat::addRow(const std::vector<float>& row)
{
	if (m_mat.size() > 0 && row.size() != m_shape.cols)
		throw new std::invalid_argument("The given row is to big!");

	m_mat.insert(m_mat.begin(), row.begin(), row.end());
}

float& Mat::operator()(const size_t row, const size_t col)
{
	if (row >= m_shape.rows || col >= m_shape.cols)
		throw std::out_of_range("Index out of range");

	return m_mat[row * m_shape.cols + col];
}

const float& Mat::operator()(const size_t row, const size_t col) const
{
	if (row >= m_shape.rows || col >= m_shape.cols)
		throw std::out_of_range("Index out of range");
	return m_mat[row * m_shape.cols + col];
}