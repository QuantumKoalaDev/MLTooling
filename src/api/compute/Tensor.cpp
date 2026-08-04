module;

#include <mlt/macros.hpp>
#include <mlt/internal/compute/core/MltArray.hpp>

#include <cstddef>

module mlt.compute.Tensor;

using namespace mlt::core;
using namespace mlt::compute;
using namespace mlt::compute::core;

mlt::core::Result<Tensor> Tensor::from(std::initializer_list<size_t> shape) noexcept
{
    MLT_TRY(tmpShape, DefaultSizeArray::from(shape));
    MLT_TRY(arr, MltArray::from(std::move(tmpShape)));

    return Tensor(std::move(arr));
}

mlt::core::Result<Tensor> Tensor::from(std::span<const float> buf, std::initializer_list<size_t> shape) noexcept
{
    MLT_TRY(tmpShape, DefaultSizeArray::from(shape));
    MLT_TRY(arr, MltArray::from(buf, std::move(tmpShape)));

    return Tensor(std::move(arr));
}

mlt::core::Result<Tensor> Tensor::copyFrom(const Tensor& tensor) noexcept
{
    MLT_TRY(cpyArr, MltArray::copyFrom(tensor.mArray));
    return Tensor(std::move(cpyArr));
}

mlt::core::Result<Tensor> Tensor::transpose() const noexcept
{
    MLT_TRY(transposedArr, mArray.transpose());
    return Tensor(std::move(transposedArr));
}
