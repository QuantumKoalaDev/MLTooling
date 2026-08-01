#pragma once

#include <expected>
#include <mlt/internal/compute/core/DType.hpp>
#include <mlt/internal/compute/core/RefCount.hpp>
#include <mlt/internal/compute/core/Error.hpp>

#include <cstddef>
#include <type_traits>

import mlt.core.error;
import mlt.internal.compute.core.sizearray;
import mlt.internal.core.storage;

#define CHECK_DTYPE()                                                      \
    do {                                                                   \
        if (dType != DTypeMapping<T>::value)                               \
            return std::unexpected(                                        \
                ComputeError{                                              \
                    .type = ComputeErrorType::TypeMismatch,                        \
                    .msg = getTypeMismatchMsg(toString(dType), typeid(T).name())  \
                }                                                          \
            );                                                             \
    } while (0)

#define CHECK_RANK()                                                      \
    do {                                                                  \
        if (idxLength != rank)                                            \
            return std::unexpected(                                       \
                ComputeError{                                             \
                    .type = ComputeErrorType::RankMismatch,               \
                    .msg = getRankMismatchMsg(rank, idxLength)            \
                }                                                         \
            );                                                            \
    } while (0)

#define CHECK_BOUNDS(val, max)                                            \
    do {                                                                  \
        if (val >= max)                                                   \
            return std::unexpected(                                       \
                ComputeError{                                             \
                    .type = ComputeErrorType::OutOfBounds,                \
                    .msg = getOutOfBoundsMsg(shape[i], indices[i])        \
                }                                                         \
            );                                                            \
    } while (0)



namespace mlt::compute::core 
{
    enum class DimType
    {
        COLUMN_MAJOR,
        ROW_MAJOR
    };


    struct MltArray
    {
        using default_dType = float;
        static constexpr DType DEFAULT_DTYPE = DType::FLOAT32;
        static constexpr DimType DEFAULT_DIM_TYPE = DimType::ROW_MAJOR;

        Ref<Storage> data;
        SizeArray<DEFAULT_DIM> strides;
        SizeArray<DEFAULT_DIM> shape;
        size_t offset;
        DType dType;
        DimType dimType;

        // shape nxnxRowxCol
        static std::expected<MltArray, mlt::core::MltError> from(
            DefaultSizeArray&& shape,
            DType dType = DEFAULT_DTYPE,
            DimType dimType = DEFAULT_DIM_TYPE
        ) noexcept;

        template <typename T>
        static MltArray from(
            const T* data,
            DefaultSizeArray&& shape,
            DType dType = DEFAULT_DTYPE,
            DimType dimType = DEFAULT_DIM_TYPE
        )
        {
            
        }

        // MltArray transpose();

        template<typename T = default_dType, typename... Indices>
        requires (std::is_convertible_v<Indices, size_t>&& ...)
        std::expected<T*, ComputeError> at(Indices... idx)
        {
            CHECK_DTYPE();
            constexpr size_t idxLength = sizeof...(Indices);
            const size_t rank = shape.size();
            CHECK_RANK();

            size_t indices[] = { static_cast<size_t>(idx)... };
            size_t pos = offset;

            for (size_t i = 0; i < idxLength; ++i)
            {
                CHECK_BOUNDS(indices[i], shape[i]);
                pos += indices[i] * strides[i];
            }
            
            return reinterpret_cast<T*>(getStorageData()) + pos;
        }
        
        template <typename T = default_dType, typename... Indices>
        requires(std::is_convertible_v<Indices, size_t> && ...)
        T at(Indices... idx) const
        {
            CHECK_DTYPE();
            constexpr size_t idxLength = sizeof...(Indices);
            const size_t rank = shape.size();
            CHECK_RANK();

            const size_t indices[] = { static_cast<size_t>(idx)... };
            size_t pos = offset;

            for (size_t i = 0; i < idxLength; ++i)
            {
                CHECK_BOUNDS(indices[i], shape[i]);
                pos += indices[i] * strides[i];
            }

            return reinterpret_cast<T*>(getStorageData())[pos];
        }

        private:
        MltArray(
            Ref<Storage> storage,
            DefaultSizeArray&& shape,
            DefaultSizeArray&& strides,
            DType dType,
            DimType dimType
        ) noexcept;
        std::byte* getStorageData();
        std::byte* getStorageData() const;
    };
}
