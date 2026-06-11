#pragma once

#include <expected>

#include <mlt/internal/compute/core/Error.hpp>
#include <mlt/internal/compute/core/MltArray.hpp>

namespace mlt::compute::ops 
{
    std::expected<core::MltArray, core::ComputeError> matmul(const core::MltArray& a, const core::MltArray& b);
    std::expected<core::MltArray, core::ComputeError> add(const core::MltArray& a, const core::MltArray& b);
    std::expected<core::MltArray, core::ComputeError> sum(const core::MltArray& a);
    std::expected<core::MltArray, core::ComputeError> sigmoid(const core::MltArray& a);
}
