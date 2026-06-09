#include <mlt/internal/compute/core/MltArray.hpp>

using namespace mlt::compute::core;

void computeStrides(
    SizeArray<DEFAULT_DIM>& stride,
    const SizeArray<DEFAULT_DIM>& shape,
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
            throw NotImplementedException();
            
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

MltArray::MltArray(SizeArray<DEFAULT_DIM>&& shape, DType dType, DimType dimType)
    : shape(std::move(shape)), offset(0), dType(dType), dimType(dimType)
{
    strides = SizeArray(this->shape.size());

    computeStrides(strides, this->shape, 1, dimType);
    data = Storage::alloc(product(this->shape.getData(), this->shape.size()) * toByteCount(dType));
}

MltArray MltArray::from(SizeArray<DEFAULT_DIM>&& shape, const DType dType, const DimType dimType)
{
    return MltArray(std::move(shape), dType, dimType);
}

MltArray MltArray::transpose()
{
    MltArray transposed = *this;

    const size_t lastPos = transposed.shape.size() - 1;
    const size_t secoundLastPos = transposed.shape.size() - 2;
 
    transposed.shape[lastPos] = shape[secoundLastPos];
    transposed.shape[secoundLastPos] = shape[lastPos];

    transposed.strides[lastPos] = strides[secoundLastPos];
    transposed.strides[secoundLastPos] = strides[lastPos];

    return transposed;
}
