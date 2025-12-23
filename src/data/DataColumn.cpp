#include "../include/data/DataColumn.hpp"

#include <algorithm>
#include <format>
#include <stdexcept>
#include <sstream>
#include <typeinfo>

using namespace mlt::data;

template <typename T>
DataColumn<T>::DataColumn(std::string name, std::vector<T> fields)
	: m_name(std::move(name)), m_data(std::move(fields))
{}

template <typename T>
const T& DataColumn<T>::operator()(size_t index) const
{
	if (index >= m_data.size())
	{
		throw std::out_of_range(
			std::format(
				"DataColumn '{}' out of range. Got {}, valid range is [0, {}].",
				m_name, index, m_data.size()
			)
		);
	}

	return m_data[index];
}

template <typename T>
std::type_index DataColumn<T>::getType() const { return typeid(T); }

template <typename T>
const std::string& DataColumn<T>::getName() const { return m_name; }

template <typename T>
size_t DataColumn<T>::getSize() const { return m_data.size(); }

template <typename T>
std::span<const T> DataColumn<T>::getData() const { return m_data; }

template <typename T>
void DataColumn<T>::setName(std::string_view newName) { m_name = newName; }

template <typename T>
void DataColumn<T>::appendValue(T value) { m_data.push_back(std::move(value)); }

template <typename T>
void DataColumn<T>::replaceValues(const T& oldValue, const T& newValue)
{
	std::replace(m_data.begin(), m_data.end(), oldValue, newValue);
}

template <typename T>
std::string DataColumn<T>::toString() const
{
	std::ostringstream oss{};
	oss << m_name << '\n';

	for (const T& item : m_data)
		oss << item << '\n';

	return oss.str();
}

template class DataColumn<int>;
template class DataColumn<float>;
template class DataColumn<std::string>;
