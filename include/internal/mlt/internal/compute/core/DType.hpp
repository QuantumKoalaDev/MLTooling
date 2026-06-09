#pragma once

#include <string_view>

namespace mlt::compute::core
{
    enum class DType
    {
        FLOAT32,
        FLOAT64,
    };

    constexpr std::string_view toString(DType dtype)
    {
        switch (dtype)
        {
            case DType::FLOAT32: return "float32";
            case DType:: FLOAT64: return "float64";
        }

        return "UNKNOWN";
    }

    constexpr size_t toByteCount(DType type)
    {
        switch (type)
        {
            case DType::FLOAT32: return sizeof(float);
            case DType::FLOAT64: return sizeof(double);
        }
    }


    template <typename T>
    struct DTypeMapping;

    template <>
    struct DTypeMapping<float>
    {
        static constexpr DType value = DType::FLOAT32;
    };

    template <>
    struct DTypeMapping<double>
    {
        static constexpr DType value = DType::FLOAT64;
    };
    
}
