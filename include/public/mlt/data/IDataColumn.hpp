#pragma once

#include <mlt/data/dataUtils.hpp>

namespace mlt::data
{
    /// @class IDataColumn
    /// @brief Base class for all DataFrame columns.
    ///
    /// IDataColumn enables heterogeneous data in a DataFrame via polymorphism.
    class IDataColumn
    {
      public:
        virtual ~IDataColumn() = default;
        [[nodiscard]] virtual DType getType() const noexcept = 0;
        [[nodiscard]] virtual size_t getSize() const noexcept = 0;
    };
} // namespace mlt::data
