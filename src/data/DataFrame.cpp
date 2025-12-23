#include "../include/data/DataFrame.hpp"

using namespace mlt::core;
using namespace mlt::data;


Shape DataFrame::getShape() const { return m_shape; }

const ColumnBase& DataFrame::operator[](const std::string& colName)
{
	size_t colIndex = m_indexMap.at(colName);
	return *m_data[colIndex];
}

void DataFrame::appendCol(std::unique_ptr<ColumnBase> col)
{
	size_t nextIndex = m_data.size();
	m_indexMap[col.get()->getName()] = nextIndex;

	m_data.push_back(std::move(col));
	m_shape.cols++;
}
