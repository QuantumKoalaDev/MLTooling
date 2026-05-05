#include "mlt/math/Vector.hpp"
#include "mlt/models/LineareRegression.hpp"
#include <iomanip>
#include <ios>
#include <iostream>
#include <span>
#include <sstream>
#include <string>

#include <MLTooling.hpp>
#include <mlt/Math.hpp>

using namespace mlt::math::datastructures;

template <typename T> std::string toString(const std::vector<T>& v)
{
    std::ostringstream oss;
    oss << "[";

    for (size_t i = 0; i < v.size(); ++i)
    {
        oss << v[i];
        if (i + 1 < v.size())
            oss << ", ";
    }

    oss << "]";
    return oss.str();
}

static void LinearRegressionNewExample()
{
    float xData[] = {0.f, 1.f, 2.f, 3.f, 4.f};
    float yData[] = {-14.f, -7.f, 0.f, 7.f, 14.f};
    std::span<float> spanX(xData);
    std::span<float> spanY(yData);

    const Matrix<float> xDataMat = Matrix<float>(5, 1, spanX);
    const Vector<float> yDataVec = Vector<float>(spanY);
    const float lr = 0.1f;
    const size_t epochs = 500;

    mlt::models::LinearRegression model = mlt::models::LinearRegression();
    model.fit(xDataMat, yDataVec, lr, epochs);

    Vector<float> testPred = Vector<float>(1);
    testPred[0] = 20.f;

    std::cout << std::fixed << std::setprecision(8) << model.predict(testPred) << std::endl;
}

int main()
{
    LinearRegressionNewExample();
}
