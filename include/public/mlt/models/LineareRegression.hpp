#pragma once

#include "mlt/math/Matrix.hpp"
#include <mlt/math/Vector.hpp>

namespace mlt::models
{
    /// @class LinearRegression
    class LinearRegression
    {
      private:
        mlt::math::Vector<float> mWeights;
        float mBias;

      public:
        LinearRegression();
        ~LinearRegression() = default;

        float predict(const mlt::math::Vector<float>& features) const;
        void
        fit(const mlt::math::Matrix<float>& xData,
            const mlt::math::Vector<float>& yData, float learningRate, size_t epochs);
    };
} // namespace mlt::models
