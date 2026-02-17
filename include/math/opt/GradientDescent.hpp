#pragma once

#include "Container/Mat.hpp"

#include <functional>
#include <span>
#include <vector>

namespace mlt::math::opt
{
    void gradientDescentFloat(
        const Container::Mat& x,
        std::span<const float> y,
        std::vector<float>& weights,
        float& bias,
        float learningRate,
        size_t epochs,
        const std::function<float(const std::span<const float>&, const std::span<const float>&)>& loss
    ) noexcept;
}