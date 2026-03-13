#include <Models/LinearRegressionModel.hpp>

#include <algorithm>
#include <stdexcept>

using namespace Models;

LinearRegressionModel::LinearRegressionModel() : m_bias(0.f) {}

float LinearRegressionModel::predict(const std::vector<float>& xFeatures) const
{
    float prediction = 0;

    for (size_t featurePos = 0; featurePos < xFeatures.size(); featurePos++)
    {
        prediction += m_weights[featurePos] * xFeatures[featurePos];
    }

    return prediction + m_bias;
}

void LinearRegressionModel::fit(
    const Container::Mat& xData, const std::vector<float>& yData, const float learningRate, const unsigned int epochs
)
{
    const Container::Shape xDataShape = xData.getShape();

    if (xDataShape.rows != yData.size())
        throw std::invalid_argument("The size of xData and yData does not match");

    m_weights = std::vector(xDataShape.cols, 0.f);
    m_bias = 0.f;

    const size_t n = xDataShape.rows;
    const float mseHalf = 2.f / static_cast<float>(n);

    for (unsigned int epoch = 0; epoch <= epochs; epoch++)
    {
        std::vector<float> gradW;
        gradW.resize(xDataShape.cols);
        float gradB = 0.f;

        for (size_t rowId = 0; rowId < n; rowId++)
        {
            const std::vector<float>& rowData = xData.getRow(rowId);
            const float& y = yData[rowId];

            const float y_hat = predict(rowData);
            const float diff = y_hat - y;

            // Calculating MSE for w: dL/dw = (2/N) * diff * x
            for (size_t colId = 0; colId < xDataShape.cols; colId++)
            {
                gradW[colId] += diff * rowData[colId];
            }

            // dL/db = (2/N) * diff
            gradB += diff;
        }

        std::ranges::for_each(gradW, [&](float& item) { item = mseHalf * item; });
        gradB = mseHalf * gradB;

        updateWeights(gradW, learningRate);
        updateBias(gradB, learningRate);
    }
}

void LinearRegressionModel::updateWeights(const std::vector<float>& weightGradients, const float learningRate)
{
    if (m_weights.size() != weightGradients.size())
        throw std::invalid_argument("Size of weights and weight gradients does not match");

    for (size_t i = 0; i < m_weights.size(); i++)
    {
        m_weights[i] -= learningRate * weightGradients[i];
    }
}

void LinearRegressionModel::updateBias(const float biasGradient, const float learningRate)
{
    m_bias -= learningRate * biasGradient;
}