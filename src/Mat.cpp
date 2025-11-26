#include "../include/Mat.h"

#include <stdexcept>

Mat::Mat(): m_mat({})
{}

Mat::Mat(std::vector<std::vector<float>>& mat): m_mat(std::move(mat))
{}

std::vector<float> Mat::getRow(size_t rowIndex) const
{
	size_t numberRows = m_mat.size();

	if (rowIndex >= numberRows)
		throw new std::invalid_argument("Row index out of bound");

	return m_mat[rowIndex];
}

Shape Mat::getShape() const
{
	return { m_mat.size(), m_mat[0].size() };
}

void Mat::addRow(const std::vector<float>& row)
{
	if (m_mat.size() > 0 && row.size() != m_mat[0].size())
		throw new std::invalid_argument("This given row is to big!");

	m_mat.push_back(row);
}