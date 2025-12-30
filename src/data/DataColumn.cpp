#include "data/DataColumn.hpp"
#include "core/Exceptions.hpp"

#include <stdexcept>

using namespace mlt::data;
using namespace mlt::core;

template <typename T>
DataColumn<T>::DataColumn<T>(std::vector<T> data) : m_data(std::move(data))
{}

template <typename T>
DataColumn<T>::DataColumn<T>(size_t size) : m_data(size)
{}

template <typename T>
DataColumn<T>::DataColumn<T>() : DataColumn(0)
{}

template <typename T>
T DataColumn<T>::operator[](size_t row) const
{
	size_t dataSize = m_data.size();
	if (row >= dataSize)
		throw std::out_of_range(std::format("DataColumn size: {}, got {}.", dataSize, row));

	return m_data[row];
}

template <typename T>
T& DataColumn<T>::operator[](size_t row)
{
	size_t dataSize = m_data.size();
	if (row >= m_data.size())
		throw std::out_of_range(std::format("DataColumn size: {}, got {}.", dataSize, row));

	return m_data[row];
}

template <typename T>
bool DataColumn<T>::isEqual(DataColumn<T>& other) const
{
	return m_data == other.m_data;
}

template <typename T>
DType DataColumn<T>::getType() const noexcept
{
	return DTypeOf<T>::value;
}

template <typename T>
size_t DataColumn<T>::getSize() const noexcept
{
	return m_data.size();
}

template <typename T>
void DataColumn<T>::append(T data)
{
	m_data.push_back(data);
}

template <typename T>
void DataColumn<T>::append(std::vector<T> data)
{
	m_data.reserve(m_data.size() + data.size());

	m_data.insert(
		m_data.end(),
		std::make_move_iterator(data.begin()),
		std::make_move_iterator(data.end())
	);
}

template <typename T>
void DataColumn<T>::append(DataColumn<T> column)
{
	m_data.reserve(m_data.size() + column.m_data.size());

	m_data.insert(
		m_data.end(),
		std::make_move_iterator(column.m_data.begin()),
		std::make_move_iterator(column.m_data.end())
	);
}

template class DataColumn<int64_t>;
template class DataColumn<float>;
template class DataColumn<double>;
template class DataColumn<DateTime>;
template class DataColumn<std::string>;
