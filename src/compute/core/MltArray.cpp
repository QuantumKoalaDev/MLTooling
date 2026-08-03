#include <expected>
#include <mlt/internal/compute/core/MltArray.hpp>

#include <ostream>

import mlt.core.error;

using namespace mlt::compute::core;

size_t product(const size_t* arr, size_t n)
{
    size_t result = 1;

    for (size_t i = 0; i < n; ++i)
        result *= arr[i];

    return result;
}

MltArray::MltArray(
    Ref<Storage> storage,
    DefaultSizeArray&& shape,
    DefaultSizeArray&& strides,
    DType dType,
    DimType dimType
) noexcept
    :   data(storage),
        shape(std::move(shape)),
        strides(std::move(strides)),
        offset(0),
        dType(dType),
        dimType(dimType)
{}

std::expected<MltArray, mlt::core::MltError> MltArray::from(SizeArray<DEFAULT_DIM>&& shape, const DType dType, const DimType dimType) noexcept
{
    std::expected<DefaultSizeArray, mlt::core::MltError> cStrides = DefaultSizeArray::from(shape.size());
    
    if (!cStrides)
        return std::unexpected(cStrides.error());

    DefaultSizeArray strides = std::move(cStrides).value(); 
    MltArray::computeStrides(strides, shape, 1, dimType);
    const size_t bytes = product(shape.getData(), shape.size());
    std::expected<Ref<Storage>, mlt::core::MltError> cStorage = Storage::alloc(product(shape.getData(), shape.size()) * toByteCount(dType));

    if (!cStorage)
        return std::unexpected(cStorage.error());
    
    Ref<Storage> storage = cStorage.value();


    return MltArray(
        storage,
        std::move(shape),
        std::move(strides),
        dType,
        dimType
    );
}

//MltArray MltArray::transpose()
//{
//    MltArray transposed = *this;

//    const size_t shapeLen = transposed.shape.size();
//    SizeArray<DEFAULT_DIM> newShape = SizeArray(shapeLen);
//    SizeArray<DEFAULT_DIM> newStrides = SizeArray(shapeLen);


//    for (size_t i = 0; i < shapeLen; ++i)
//        newShape[i] = transposed.shape[shapeLen - i - 1];
               
//    for (size_t i = 0; i < shapeLen; ++i)
//        newStrides[i] = transposed.strides[shapeLen - i - 1];

//    transposed.shape = newShape;
//    transposed.strides = newStrides;

//    return transposed;
//}

