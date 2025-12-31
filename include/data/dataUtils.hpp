#pragma once

#include <chrono>
#include <cstddef>
#include <cstdint>
#include <string>

namespace mlt::data
{
    // Alias for a high-resolution timestamp using system_clock with nanosecond precision.
    using DateTime = std::chrono::time_point<std::chrono::system_clock, std::chrono::nanoseconds>;

    /// @enum
    /// @brief Enumeration of all supported data types in the DataFrame.
    enum class DType : uint8_t
    {
        INT64,
        FLOAT32,
        FLOAT64,
        DATETIME,
        STRING,
        OBJECT
    };

    // Primary template: maps a C++ type T to its corresponding DType.
    template <typename T> struct DTypeOf;

    // Specializations of DTypeOf for supported types:
    template <> struct DTypeOf<int64_t>
    {
        static constexpr DType value = DType::INT64;
    };

    template <> struct DTypeOf<float>
    {
        static constexpr DType value = DType::FLOAT32;
    };

    template <> struct DTypeOf<double>
    {
        static constexpr DType value = DType::FLOAT64;
    };

    template <> struct DTypeOf<std::string>
    {
        static constexpr DType value = DType::STRING;
    };

    template <> struct DTypeOf<DateTime>
    {
        static constexpr DType value = DType::DATETIME;
    };

    /// @struct
    /// @brief Represents metadata for a single column in a DataFrame.
    ///
    /// ColumnEntry stores the column's name, its position in the DataFrame,
    /// and its data type (DType).
    struct ColumnEntry
    {
        std::string name;
        size_t index;
        DType type;
    };
} // namespace mlt::data