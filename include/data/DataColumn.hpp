#include "data/dataUtils.hpp"
#include "data/IDataColumn.hpp"

#include <cstddef>
#include <cstdint>
#include <string>
#include <vector>

namespace mlt::data
{
	template <typename T>
	class DataColumn : public IDataColumn
	{
		std::vector<T> m_data;

	public:
		DataColumn(std::vector<T> data);
		DataColumn(size_t size);
		DataColumn();
		~DataColumn() = default;


		T operator[](size_t row) const;
		T& operator[](size_t row);

		bool isEqual(DataColumn& other) const;

		DType getType() const noexcept override;
		size_t getSize() const noexcept override;

		void append(T data);
		void append(std::vector<T> data);
		void append(DataColumn<T> column);
	};

	extern template class DataColumn<int64_t>;
	extern template class DataColumn<float>;
	extern template class DataColumn<double>;
	extern template class DataColumn<DateTime>;
	extern template class DataColumn<std::string>;
}
