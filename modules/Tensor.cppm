module;

#include <mlt/internal/compute/core/MltArray.hpp>

#include <span>

export module mlt.compute.Tensor;

namespace mlt::compute
{
    export class Tensor
    {
        mlt::compute::core::MltArray arr;

        public:
        static Tensor from(std::initializer_list<size_t> shape);
        static Tensor from(std::span<size_t> shape);
    };
}
