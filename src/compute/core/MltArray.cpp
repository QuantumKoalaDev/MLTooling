#include <expected>
#include <mlt/internal/compute/core/MltArray.hpp>

import mlt.core.error;

using namespace mlt::compute::core;

void computeStrides(
    DefaultSizeArray& stride,
    const DefaultSizeArray& shape,
    const size_t startStride,
    const DimType type
)
{
    switch (type) {
        case DimType::ROW_MAJOR:
        {
            const size_t len = shape.size();
            size_t currentStride = startStride;

            for (size_t i = len; i > 0; --i)
            {
                const size_t pos = i - 1;
                stride[pos] = currentStride;
                currentStride *= shape[pos];
            }

            break;
        }
        case DimType::COLUMN_MAJOR:
        {
            break;
        }
    }

}

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
    computeStrides(strides, shape, 1, dimType);
    std::expected<Ref<Storage>, mlt::core::MltError> cStorage = Storage::alloc(product(shape.getData(), shape.size() * toByteCount(dType)));

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
//
//    const size_t shapeLen = transposed.shape.size();
//    SizeArray<DEFAULT_DIM> newShape = SizeArray(shapeLen);
//    SizeArray<DEFAULT_DIM> newStrides = SizeArray(shapeLen);
//
//
//    for (size_t i = 0; i < shapeLen; ++i)
//        newShape[i] = transposed.shape[shapeLen - i - 1];
//               
//    for (size_t i = 0; i < shapeLen; ++i)
//        newStrides[i] = transposed.strides[shapeLen - i - 1];
//
//    transposed.shape = newShape;
//    transposed.strides = newStrides;
//
//    return transposed;
//}

std::byte* MltArray::getStorageData()
{
    return data->data;
}

std::byte* MltArray::getStorageData() const
{
    return data->data;
}
