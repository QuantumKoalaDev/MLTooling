module;

#include <mlt/macros.hpp>

#include <cstddef>
#include <span>

module mlt.compute.Tensor;
import mlt.internal.compute.core.mltarray;
import mlt.internal.compute.core.sizearray;

using namespace mlt::core;
using namespace mlt::compute;
using namespace mlt::compute::core;

mlt::core::Result<Tensor> Tensor::from(std::initializer_list<size_t> shape) noexcept
{
    MLT_TRY(arr, MltArray::from(DefaultSizeArray(shape)));

    return Tensor(std::move(arr));
}

mlt::core::Result<Tensor> Tensor::from(std::span<const float> buf, std::initializer_list<size_t> shape) noexcept
{
    MLT_TRY(arr, MltArray::from(buf, DefaultSizeArray(shape)));

    return Tensor(std::move(arr));
}

Tensor Tensor::transpose() const noexcept
{
    MltArray transposedArr = mArray.transpose();
    return Tensor(transposedArr);
}
