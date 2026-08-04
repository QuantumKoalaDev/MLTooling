module;

#include <mlt/macros.hpp>
#include <mlt/internal/compute/core/MltArray.hpp>

#include <span>

export module mlt.compute.Tensor;

import mlt.core.error;

namespace mlt::compute
{
    export class Tensor
    {
        mlt::compute::core::MltArray mArray;
        
        Tensor(mlt::compute::core::MltArray&& array) : mArray(std::move(array))
        {}

        public:
        Tensor(const Tensor&) = delete;
        Tensor& operator=(const Tensor&) = delete;

        Tensor(Tensor&&) noexcept = default;
        Tensor& operator=(Tensor&&) noexcept = default;

        static mlt::core::Result<Tensor> from(std::initializer_list<size_t> shape) noexcept;
        static mlt::core::Result<Tensor> from(std::span<const float> buf, std::initializer_list<size_t> shape) noexcept;
        static mlt::core::Result<Tensor> copyFrom(const Tensor& tensor) noexcept;

        mlt::core::Result<Tensor> transpose() const noexcept;

        template <typename... Indices>
        mlt::core::Result<float*> at(Indices... idx) noexcept
        {
            MLT_TRY(val, mArray.at(idx...));
            return val;
        }

        template <typename... Indices>
        mlt::core::Result<float> at(Indices... idx) const noexcept
        {
            MLT_TRY(val, mArray.at(idx...));
            return val;
        }
    };
}
