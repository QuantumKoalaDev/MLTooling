#include <mlt/data/DataFrame.hpp>

using namespace mlt::core;
using namespace mlt::data;

Shape DataFrame::getShape() const
{
    return m_shape;
}

void DataFrame::append(const std::string& name, std::unique_ptr<IDataColumn> column)
{
    const size_t currentLength = m_data.size();

    if (currentLength == 0)
    {
        m_shape.cols = 1;
        m_shape.rows = column->getSize();
    }

    m_data.push_back(std::move(column));
    m_labelMap[name] = currentLength;
    m_shape.rows = currentLength;
}

void DataFrame::drop(const std::string& name)
{
    if (m_shape.cols == 0)
        throw std::runtime_error("DataFrame::drop() called on empty DataFrame");

    const size_t position = m_labelMap.at(name);
    m_labelMap.erase(name);
    m_data.erase(m_data.begin() + static_cast<long>(position));
    m_shape.cols -= 1;
}