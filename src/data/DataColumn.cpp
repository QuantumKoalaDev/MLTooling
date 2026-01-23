#include "data/DataColumn.hpp"
#include "core/Exceptions.hpp"

#include <format>
#include <stdexcept>

using namespace mlt::data;
using namespace mlt::core;

template <typename T> DataColumn<T>::DataColumn(std::vector<T> data, std::vector<bool> validityMask) : m_data(std::move(data))
{
    if (!validityMask.empty() && m_data.size() != validityMask.size())
        throw std::invalid_argument("Validity mask must be the same size as the data.");

    if (validityMask.empty())
    {
        m_validityMask = std::vector<bool>(validityMask.size(), true);
    }
    else
    {
        m_validityMask = std::move(validityMask);
    }
}

template <typename T> DataColumn<T>::DataColumn(size_t size) : m_data(size)
{
    m_validityMask = std::vector<bool>(size, true);
}

template <typename T> DataColumn<T>::DataColumn() : DataColumn(0) {}

template <typename T> T DataColumn<T>::operator[](size_t row) const
{
    if (size_t dataSize = m_data.size(); row >= dataSize)
        throw std::out_of_range(std::format("DataColumn size: {}, got {}.", dataSize, row));

    return m_data[row];
}

template <typename T> T& DataColumn<T>::operator[](size_t row)
{
    size_t dataSize = m_data.size();
    if (row >= m_data.size())
        throw std::out_of_range(std::format("DataColumn size: {}, got {}.", dataSize, row));

    return m_data[row];
}

template <typename T> bool DataColumn<T>::isEqual(DataColumn<T>& other) const
{
    return m_data == other.m_data;
}

template <typename T> DType DataColumn<T>::getType() const noexcept
{
    return DTypeOf<T>::value;
}

template <typename T> size_t DataColumn<T>::getSize() const noexcept
{
    return m_data.size();
}

template <typename T> DataColumnInfo DataColumn<T>::getInfo() const noexcept
{
    DataColumnInfo info {};
    info.dtype = getType();
    info.size = getSize();
    info.invalidRows = countNa();

    return info;
}

template <typename T> std::optional<T> DataColumn<T>::get(size_t row) const
{
    if (size_t dataSize = m_data.size(); row >= dataSize)
        throw std::out_of_range(std::format("DataColumn size: {}, got {}.", dataSize, row));

    if (!m_validityMask[row])
        return std::nullopt;

    return m_data[row];
}

template <typename T> void DataColumn<T>::set(size_t row, T value, const bool validity)
{
    if (size_t dataSize = m_data.size(); row >= dataSize)
        throw std::out_of_range(std::format("DataColumn size: {}, got {}.", dataSize, row));

    m_data[row] = std::move(value);
    m_validityMask[row] = validity;
}

template <typename T> void DataColumn<T>::set(size_t row, const bool valid)
{
    if (size_t dataSize = m_data.size(); row >= dataSize)
        throw std::out_of_range(std::format("DataColumn size: {}, got {}.", dataSize, row));
    m_validityMask[row] = valid;

}

template <typename T> void DataColumn<T>::append(T data, const bool valid)
{
    m_data.push_back(data);
    m_validityMask.push_back(valid);
}

template <typename T> void DataColumn<T>::append(std::vector<T> data, const std::vector<bool>& validityMask)
{
    if (validityMask.empty() == 0 && data.size() != validityMask.size())
        throw std::invalid_argument("Validity mask must be the same size as the appended data.");

    m_data.reserve(m_data.size() + data.size());
    m_validityMask.reserve(m_validityMask.size() + data.size());

    m_data.insert(m_data.end(), std::make_move_iterator(data.begin()), std::make_move_iterator(data.end()));

    for (size_t i = 0; i < data.size(); ++i)
        m_validityMask.emplace_back(true);
}

template <typename T> void DataColumn<T>::append(DataColumn<T> column)
{
    m_data.reserve(m_data.size() + column.m_data.size());
    m_data.insert(
        m_data.end(),
        std::make_move_iterator(column.m_data.begin()),
        std::make_move_iterator(column.m_data.end())
    );

    m_validityMask.reserve(m_validityMask.size() + column.m_validityMask.size());
    m_validityMask.insert(
        m_validityMask.end(),
        std::make_move_iterator(column.m_validityMask.begin()),
        std::make_move_iterator(column.m_validityMask.end())
    );
}

template <typename T> void DataColumn<T>::remove(size_t row)
{
    if (row > m_data.size())
        throw std::out_of_range(std::format("DataColumn index out of range. (got {}, expected {}", row, m_data.size()));

    using diff_t = std::vector<T>::difference_type;
    diff_t rowDiff = static_cast<diff_t>(row);
    m_data.erase(m_data.begin() + rowDiff);
    m_validityMask.erase(m_validityMask.begin() + rowDiff);
}

template <typename T> size_t DataColumn<T>::countNa() const
{
    return std::count(m_validityMask.begin(), m_validityMask.end(), false);
}

namespace mlt::data
{
    template class DataColumn<int64_t>;
    template class DataColumn<float>;
    template class DataColumn<double>;
    template class DataColumn<DateTime>;
    template class DataColumn<std::string>;
} // namespace mlt::data
