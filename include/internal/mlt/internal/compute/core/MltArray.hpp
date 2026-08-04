#pragma once

#include <expected>
#include <mlt/internal/compute/core/DType.hpp>
#include <mlt/internal/compute/core/RefCount.hpp>
#include <mlt/internal/compute/core/Error.hpp>

#include <cassert>
#include <cstddef>
#include <span>
#include <type_traits>

import mlt.core.error;
import mlt.internal.compute.core.sizearray;
import mlt.internal.core.storage;

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
        DefaultSizeArray strides;
        DefaultSizeArray shape;
        size_t offset;
        DType dType;
        DimType dimType;

        MltArray(const MltArray&) = delete;
        MltArray& operator=(const MltArray&) = delete;

        MltArray(MltArray&&) noexcept = default;
        MltArray& operator=(MltArray&&) noexcept = default;

        template <typename T = default_dType, typename... Indices>
        requires(std::is_convertible_v<Indices, size_t> &&...)
        T& operator[](Indices... idx)
        {
            assert(DTypeMapping<T>::value == dType);
            constexpr size_t idxLength = sizeof...(Indices);
            assert(shape.size() == idxLength);
            const size_t indices[] = { static_cast<size_t>(idx)... };
            size_t pos = offset;

            for (size_t i = 0; i < idxLength; ++i)
                pos += indices[i] * strides[i];

            return *(reinterpret_cast<T*>(data->data) + pos);
        }

        template <typename T = default_dType, typename... Indices>
        requires(std::is_convertible_v<Indices, size_t> &&...)
        const T operator[](Indices... idx) const
        {
            assert(DTypeMapping<T>::value == dType);
            constexpr size_t idxLength = sizeof...(Indices);
            assert(shape.size() == idxLength);
            const size_t indices[] = { static_cast<size_t>(idx)... };
            size_t pos = offset;

            for (size_t i = 0; i < idxLength; ++i)
                pos += indices[i] * strides[i];

            return *(reinterpret_cast<T*>(data->data) + pos);
        }
 
        // shape nxnxRowxCol
        static std::expected<MltArray, mlt::core::MltError> from(
            DefaultSizeArray&& shape,
            DType dType = DEFAULT_DTYPE,
            DimType dimType = DEFAULT_DIM_TYPE
        ) noexcept;

        template <typename T = default_dType>
        static std::expected<MltArray, mlt::core::MltError> from(
            std::span<const T> data,
            DefaultSizeArray&& shape,
            DimType dimType = DEFAULT_DIM_TYPE
        ) noexcept
        {
            std::expected<DefaultSizeArray, mlt::core::MltError> cStrides = DefaultSizeArray::from(shape.size());

            if (!cStrides)
                return std::unexpected(cStrides.error());

            DefaultSizeArray strides = std::move(cStrides).value();
            MltArray::computeStrides(strides, shape, 1, dimType);

            std::span<const std::byte> bSpan = std::as_bytes(data);
            std::expected<Ref<Storage>, mlt::core::MltError> cStorage = Storage::from(bSpan);

            if (!cStorage)
                return std::unexpected(cStorage.error());

            Ref<Storage> storage = cStorage.value();

            return MltArray(
                storage,
                std::move(shape),
                std::move(strides),
                DTypeMapping<T>::value,
                dimType
            );
        }

        static std::expected<MltArray, mlt::core::MltError> copyFrom(const MltArray& arr) noexcept;

        std::expected<MltArray, mlt::core::MltError> transpose() const noexcept;

        template<typename T = default_dType, typename... Indices>
        requires (std::is_convertible_v<Indices, size_t>&& ...)
        std::expected<T*, mlt::core::MltError> at(Indices... idx) noexcept
        {
            if (DTypeMapping<T>::value != dType)
                return std::unexpected(mlt::core::MltError::makeTypeMismatch(
                            toString(DTypeMapping<T>::value),
                            toString(dType)
                ));

            constexpr size_t idxLength = sizeof...(Indices);
            const size_t rank = shape.size();

            if (idxLength != rank)
                return std::unexpected(mlt::core::MltError::makeRankMismatch(
                    rank,
                    idxLength
                ));

            size_t indices[] = { static_cast<size_t>(idx)... };
            size_t pos = offset;

            for (size_t i = 0; i < idxLength; ++i)
            {
                if (indices[i] >= shape[i])
                    return std::unexpected(mlt::core::MltError::makeOutOfBounds(
                        indices[i],
                        shape[i]
                    ));

                pos += indices[i] * strides[i];
            }
            
            return reinterpret_cast<T*>(data->data) + pos;
        }
        
        template <typename T = default_dType, typename... Indices>
        requires(std::is_convertible_v<Indices, size_t> && ...)
        std::expected<T, mlt::core::MltError> at(Indices... idx) const noexcept
        {
            if (DTypeMapping<T>::value != dType)
                return std::unexpected(mlt::core::MltError::makeTypeMismatch(
                            toString(DTypeMapping<T>::value),
                            toString(dType)
                ));

            constexpr size_t idxLength = sizeof...(Indices);
            const size_t rank = shape.size();
 
            if (idxLength != rank)
                return std::unexpected(mlt::core::MltError::makeRankMismatch(
                    rank,
                    idxLength
                ));

            const size_t indices[] = { static_cast<size_t>(idx)... };
            size_t pos = offset;

            for (size_t i = 0; i < idxLength; ++i)
            {
                if (indices[i] >= shape[i])
                    return std::unexpected(mlt::core::MltError::makeOutOfBounds(
                        indices[i],
                        shape[i]
                    ));
 
                pos += indices[i] * strides[i];
            }

            return *(reinterpret_cast<T*>(data->data) + pos);
        }

        private:
        MltArray(
            Ref<Storage> storage,
            DefaultSizeArray&& shape,
            DefaultSizeArray&& strides,
            DType dType,
            DimType dimType
        ) noexcept;

        static void computeStrides(
            DefaultSizeArray& stride,
            const DefaultSizeArray& shape,
            const size_t startStride,
            const DimType type
        ) noexcept
        {
            switch (type)
            {
                case DimType::ROW_MAJOR:
                {
                    const size_t len = shape.size();
                    size_t currentStride = startStride;

                    for (size_t i = len; i-- > 0;)
                    {
                        stride[i] = currentStride;
                        currentStride *= shape[i];
                    }

                    break;
                }
                case DimType::COLUMN_MAJOR:
                {
                    const size_t len = shape.size();
                    size_t currentStride = startStride;

                    for (size_t i = 0; i < len; ++i)
                    {
                        stride[i] = currentStride;
                        currentStride *= shape[i];
                    }

                    break;
                }
            }
        }
    };
}
