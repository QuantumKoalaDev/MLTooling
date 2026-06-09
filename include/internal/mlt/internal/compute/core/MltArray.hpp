#pragma once

#include <mlt/internal/compute/core/DType.hpp>
#include <mlt/internal/compute/core/Exceptions.hpp>
#include <mlt/internal/compute/core/RefCount.hpp>
#include <mlt/internal/compute/core/SizeArray.hpp>
#include <mlt/internal/compute/core/Storage.hpp>

#include <cstddef>
#include <type_traits>

namespace mlt::compute::core 
{
    enum class DimType
    {
        COLUMN_MAJOR,
        ROW_MAJOR
    };


    struct MltArray
    {
        static constexpr DType DEFAULT_DTYPE = DType::FLOAT32;
        static constexpr DimType DEFAULT_DIM_TYPE = DimType::ROW_MAJOR;

        Ref<Storage> data;
        SizeArray<DEFAULT_DIM> strides;
        SizeArray<DEFAULT_DIM> shape;
        size_t offset;
        DType dType;
        DimType dimType;

        // shape nxnxRowxCol
        static MltArray from(
            SizeArray<DEFAULT_DIM>&& shape,
            DType dType = DEFAULT_DTYPE,
            DimType dimType = DEFAULT_DIM_TYPE
        );

        MltArray transpose();

        template<typename T, typename... Indices>
        requires (std::is_convertible_v<Indices, size_t>&& ...)
        T& at(Indices... idx)
        {
            if (dType != DTypeMapping<T>::value)
                throw TypeMissmatchException(toString(dType), typeid(T).name());
            
            constexpr size_t idxLength = sizeof...(Indices);
            const size_t rank = shape.size();

            if (idxLength != rank)
                throw RankMissmatchException(rank, idxLength);

            size_t indices[] = { static_cast<size_t>(idx)... };
            size_t pos = offset;

            for (size_t i = 0; i < idxLength; ++i)
            {
                if (indices[i] >= shape[i])
                    throw OutOfBoundsException(shape[i], indices[i]);
                
                pos += indices[i] * strides[i];
            }
            
            return reinterpret_cast<T*>(data->data)[pos];
        }
        
        template <typename T, typename... Indices>
        requires(std::is_convertible_v<Indices, size_t> && ...)
        T at(Indices... idx) const
        {
            if (dType != DTypeMapping<T>::value)
                throw  TypeMissmatchException(toString(dType), typeid(T).name());

            constexpr size_t idxLength = sizeof...(Indices);
            const size_t rank = shape.size();

            if (idxLength != rank)
                throw RankMissmatchException(rank, idxLength);

            const size_t indices[] = { static_cast<size_t>(idx)... };
            size_t pos = offset;

            for (size_t i = 0; i < idxLength; ++i)
            {
                if (indices[i] >= shape[i])
                    throw OutOfBoundsException(shape[i], indices[i]);

                pos += indices[i] * strides[i];
            }

            return reinterpret_cast<T*>(data->data)[pos];
        }

        private:
        MltArray(SizeArray<DEFAULT_DIM>&& shape, DType dType, DimType dimType);
    };
}
