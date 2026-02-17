#include "math/opt/GradientDescent.hpp"

#include <algorithm>

using namespace Container;
using namespace mlt::math::opt;

inline void updateWeights(std::vector<float>& weights, const std::span<const float> gradWeights, const float learningRate)
{
    for (size_t rowId = 0; rowId < weights.size(); ++rowId)
        weights[rowId] -= learningRate * gradWeights[rowId];
}

// bias = bias - bias * alpha
inline void udpateBias(float& bias, const float biasGradient, const float learningRate)
{
    bias -= biasGradient * learningRate;
}

void gradientDescentFloat(
    const Mat& x,
    std::span<const float> y,
    std::vector<float>& weights,
    float& bias,
    const float learningRate,
    const size_t epochs,
    const std::function<float(const std::span<const float>&, const std::span<const float>&)>& loss
)
{
    for (size_t epoch = 0; epoch < epochs; ++epoch)
    {
        const Shape& xShape = x.getShape();
        std::vector<float> gradWeights;
        gradWeights.resize(xShape.cols);
        float gradBias = 0.f;

        for (size_t rowId = 0; rowId < xShape.rows; ++rowId)
        {
            const std::span<const float> rowData = x.getRow(rowId);
            const float& yVal = y[rowId];

            float yHat = 0.f;

            for (size_t colId = 0; colId < xShape.cols; ++colId)
                yHat += weights[colId] * rowData[colId];
            yHat += bias;
            const float diff = yHat - yVal;

            for (size_t colId = 0; colId < xShape.cols; ++colId)
                gradWeights[colId] += diff * rowData[colId];
            gradBias += diff;
        }

        float half = 2.f / static_cast<float>(xShape.rows);
        std::ranges::for_each(gradWeights, [&](float& item) {item = half * item; });
        gradBias = half * gradBias;

        updateWeights(weights, gradWeights, learningRate);
    }
}
