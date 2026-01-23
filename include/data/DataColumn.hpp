#pragma once

#include "data/IDataColumn.hpp"
#include "data/dataUtils.hpp"

#include <string>
#include <vector>

namespace mlt::data
{
    struct DataColumnInfo
    {
        DType dtype;
        size_t size;
        size_t invalidRows;
    };

    template <typename T> class DataColumn : public IDataColumn
    {
        std::vector<T> m_data;
        std::vector<bool> m_validityMask;

      public:
        explicit DataColumn(std::vector<T> data, std::vector<bool> validityMask = std::vector<bool>());
        explicit DataColumn(size_t size);
        DataColumn();
        ~DataColumn() override = default;

        T operator[](size_t row) const;

        /// Should not be used if data might not be valid as no validity checks are performed.
        /// If data could be invalid use read() instead.
        T& operator[](size_t row);

        bool isEqual(DataColumn& other) const;

        [[nodiscard]] DType getType() const noexcept override;
        [[nodiscard]] size_t getSize() const noexcept override;
        [[nodiscard]] DataColumnInfo getInfo() const noexcept;

        [[nodiscard]] std::optional<T> get(size_t row) const;
        void set(size_t row, T value, bool validity = true);
        void set(size_t row, bool valid);

        void append(T data, bool valid = true);
        void append(std::vector<T> data, const std::vector<bool>& validityMask = std::vector<bool>());
        void append(DataColumn<T> column);

        void remove(size_t row);
        [[nodiscard]] size_t countNa() const;
    };

    extern template class DataColumn<int64_t>;
    extern template class DataColumn<float>;
    extern template class DataColumn<double>;
    extern template class DataColumn<DateTime>;
    extern template class DataColumn<std::string>;
} // namespace mlt::data

