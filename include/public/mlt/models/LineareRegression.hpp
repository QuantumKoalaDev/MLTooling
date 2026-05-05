#pragma once

#include "mlt/math/Matrix.hpp"
#include <mlt/math/Vector.hpp>

namespace mlt::models
{
    /// @class LinearRegression
    class LinearRegression
    {
      private:
        mlt::math::datastructures::Vector<float> mWeights;
        float mBias;

      public:
        LinearRegression();
        ~LinearRegression() = default;

        float predict(const mlt::math::datastructures::Vector<float>& features) const;
        void
        fit(const mlt::math::datastructures::Matrix<float>& xData,
            const mlt::math::datastructures::Vector<float>& yData, float learningRate, size_t epochs);
    };
} // namespace mlt::models
