#pragma once

#include "data/IDataColumn.hpp"
#include "data/dataUtils.hpp"

#include <string>
#include <vector>

namespace mlt::data
{
    template <typename T> class DataColumn : public IDataColumn
    {
        std::vector<T> m_data;
        std::vector<bool> m_validityMask;

      public:
        explicit DataColumn(std::vector<T> data);
        explicit DataColumn(size_t size);
        DataColumn();
        ~DataColumn() override = default;

        T operator[](size_t row) const;
        T& operator[](size_t row);

        bool isEqual(DataColumn& other) const;

        DType getType() const noexcept override;
        size_t getSize() const noexcept override;

        void append(T data, bool valid = true);
        void append(std::vector<T> data);
        void append(DataColumn<T> column);

        void remove(size_t row);
        size_t countNa();
    };

    extern template class DataColumn<int64_t>;
    extern template class DataColumn<float>;
    extern template class DataColumn<double>;
    extern template class DataColumn<DateTime>;
    extern template class DataColumn<std::string>;
} // namespace mlt::data
