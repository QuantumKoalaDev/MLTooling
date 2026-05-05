#include "mlt/math/Exceptions.hpp"
#include "mlt/math/Vector.hpp"
#include <mlt/core/Shape.hpp>
#include <mlt/models/LineareRegression.hpp>

using namespace mlt::models;
using namespace mlt::math::datastructures;

// Current workaround...
Vector<float> getRowViaCopy(const Matrix<float>& mat, size_t row)
{
    mlt::core::Shape shape = mat.getShape();

    Vector<float> result = Vector<float>(shape.cols);

    for (size_t col = 0; col < shape.cols; ++col)
        result[col] = mat[row, col];

    return result;
}

LinearRegression::LinearRegression() : mBias(0.f), mWeights(Vector<float>(1)) {}

float LinearRegression::predict(const Vector<float>& features) const
{
    float prediction = mBias;
    prediction += features.dot(mWeights);

    return prediction;
}

void LinearRegression::fit(const Matrix<float>& xData, const Vector<float>& yData, float learningRate, size_t epochs)
{
    const mlt::core::Shape xShape = xData.getShape();
    const size_t numFeatures = xShape.cols;

    if (yData.getLen() != xShape.rows)
        throw mlt::math::ShapeMismatchException(xShape.cols, xShape.rows, numFeatures, 1);

    mWeights = Vector<float>(numFeatures);
    mBias = 0.f;

    const size_t n = xShape.rows;
    const float mseHalf = 2.f / static_cast<float>(n);

    for (size_t epoch = 0; epoch <= epochs; epoch++)
    {
        Vector<float> gradW = Vector<float>(numFeatures);
        float gradB = 0.f;

        for (size_t row = 0; row < n; ++row)
        {
            Vector<float> rowData = getRowViaCopy(xData, row);
            const float y = yData[row];
            const float yHat = predict(rowData);
            const float diff = yHat - y;

            // Calculating MSE for w: dL/dw = (2/N) * diff * x
            gradW += rowData.mulScalar(diff);
            // dL/db = (2/N) * diff
            gradB += diff;
        }

        gradW = gradW.mulScalar(mseHalf);
        gradB *= mseHalf;
        mWeights -= gradW.mulScalar(learningRate);
        mBias -= learningRate * gradB;
    }
}
