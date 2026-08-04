#include <exception>
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

std::expected<MltArray, mlt::core::MltError> MltArray::from(DefaultSizeArray&& shape, const DType dType, const DimType dimType) noexcept
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

std::expected<MltArray, mlt::core::MltError> MltArray::copyFrom(const MltArray& arr) noexcept
{
    auto cpyShape = DefaultSizeArray::copyFrom(arr.shape);
    auto cpyStrides = DefaultSizeArray::copyFrom(arr.strides);
    
    if (!cpyShape)
        return std::unexpected(cpyShape.error());

    if (!cpyStrides)
        return std::unexpected(cpyStrides.error());

    DefaultSizeArray shape = std::move(cpyShape).value();
    DefaultSizeArray strides = std::move(cpyStrides).value();
    
    return MltArray(
        arr.data,
        std::move(shape),
        std::move(strides),
        arr.dType,
        arr.dimType
    );
}

std::expected<MltArray, mlt::core::MltError> MltArray::transpose() const noexcept
{
    auto cpyTransposed = copyFrom(*this);

    if (!cpyTransposed)
        return std::unexpected(cpyTransposed.error());

    MltArray transposed = std::move(cpyTransposed).value();
    const size_t shapeLen = transposed.shape.size();

    for (size_t i = 0; i < shapeLen / 2; ++i)
    {
        const size_t j = shapeLen - 1 - i;

        std::swap(transposed.shape[i], transposed.shape[j]);
        std::swap(transposed.strides[i], transposed.strides[j]);
    }

    return transposed;
}

