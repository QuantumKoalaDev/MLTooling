#include "ColumnBase.hpp"

#include <cstddef>
#include <string>
#include <string_view>
#include <span>
#include <vector>
#include <ostream>
#include <typeindex>

namespace mlt::data
{
	template <typename T>
	class DataColumn : public ColumnBase
	{
		std::string m_name;
		std::vector<T> m_data;
	public:
		~DataColumn() = default;
		DataColumn(const DataColumn& column) = default;
		DataColumn(DataColumn&&) = default;
		DataColumn& operator=(const DataColumn&) = default;
		DataColumn& operator=(DataColumn&&) = default;


		DataColumn(std::string name, std::vector<T>fields);

		const T& operator()(size_t index) const;

		std::type_index getType() const;
		const std::string& getName() const override;
		size_t getSize() const override;
		std::span<const T> getData() const;

		void setName(std::string_view newName);
		void appendValue(T value);
		void replaceValues(const T& oldValue, const T& newValue);
		std::string toString() const;
	};

	extern template class DataColumn<int>;
	extern template class DataColumn<float>;
	extern template class DataColumn<std::string>;
}