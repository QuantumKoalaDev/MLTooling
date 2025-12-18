#include "../include/Container/Mat.hpp"

#include <stdexcept>

using namespace Container;

Mat::Mat(const size_t rows, const size_t cols, const float init)
	: m_shape({rows, cols}),
	m_mat(std::vector<float>(rows * cols, init))
{}

Mat::Mat(size_t rows, size_t cols, std::vector<float> mat): m_mat(std::move(mat)), m_shape(Shape(rows, cols))
{}

std::vector<float> Mat::getRow(size_t rowIndex) const
{
	if (rowIndex >= m_shape.rows)
		throw std::invalid_argument("Row index out of bound");

	std::vector<float> row(m_mat.begin() + rowIndex * m_shape.cols, m_mat.begin() + (rowIndex + 1) * m_shape.cols);

	return row;
}

Shape Mat::getShape() const
{
	return m_shape;
}

void Mat::addRow(const std::vector<float>& row)
{
	if (m_mat.size() > 0 && row.size() != m_shape.cols)
		throw std::invalid_argument("The given row is to big!");

	m_shape.rows += 1;
	m_mat.insert(m_mat.end(), row.begin(), row.end());
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

Mat& Mat::operator+=(const Mat& other)
{
	if (m_shape.rows != other.m_shape.rows || m_shape.cols != other.m_shape.cols)
		throw std::invalid_argument("Shape mismatch");

	const size_t n = m_mat.size();

	for (size_t i = 0; i < n; ++i)
	{
		m_mat[i] += other.m_mat[i];
	}

	return *this;
}

Mat Mat::operator+(const Mat& other) const
{
	Mat result = *this;
	result += other;

	return result;
}

Mat Mat::operator*(const Mat& other) const
{
	if (m_shape.cols != other.m_shape.rows)
		throw std::invalid_argument("Shape mismatch");

	Mat result = Mat(m_shape.rows, other.m_shape.cols);

	size_t rows = m_shape.rows;
	size_t cols = m_shape.cols;
	size_t otherCols = other.m_shape.cols;

	for (size_t i = 0; i < rows; ++i)
		for (size_t j = 0; j < otherCols; ++j)
			for (size_t k = 0; k < cols; ++k)
				result.m_mat[i * otherCols + j] += m_mat[i * cols + k] * other.m_mat[k * otherCols + j];

	return result;
}