#include "math/datastructures/matrixview.hpp"
#include "math/mathstatus.hpp"
#include <math/kernels/matrixkernels.hpp>

using namespace mlt::math::datastructures;

namespace mlt::math::kernels
{
    mlt::math::mathStatus
    addMatrixFloat(const MatrixFloatView& summandOne, const MatrixFloatView& summandTwo, MatrixFloatView& result)
    {
        if (checkShapeFloat(summandTwo, summandOne) == mlt::math::MATH_SHAPE_MISSMATCH)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        if (checkShapeFloat(summandOne, result) == mlt::math::MATH_SHAPE_MISSMATCH)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        for (size_t col = 0; col < result.cols; ++col)
        {
            size_t aBase = col * summandOne.colStride;
            size_t bBase = col * summandOne.colStride;
            size_t cBase = col * result.colStride;

            for (size_t row = 0; row < result.rows; ++row)
            {
                size_t aPos = aBase + row * summandOne.rowStride;
                size_t bPos = bBase + row * summandTwo.rowStride;
                size_t cPos = cBase + row * result.rowStride;

                result.data[cPos] = summandOne.data[aPos] + summandTwo.data[bPos];
            }
        }

        return mlt::math::MATH_SUCCESS;
    }

    mlt::math::mathStatus
    addMatrixDouble(const MatrixDoubleView& summandOne, const MatrixDoubleView& summandTwo, MatrixDoubleView& result)
    {
        if (checkShapeDouble(summandOne, summandTwo) == mlt::math::MATH_SHAPE_MISSMATCH)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        if (checkShapeDouble(summandOne, summandTwo) == mlt::math::MATH_SHAPE_MISSMATCH)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        for (size_t col = 0; col < result.cols; ++col)
        {
            size_t aBase = col * summandOne.colStride;
            size_t bBase = col * summandTwo.colStride;
            size_t cBase = col * result.colStride;

            for (size_t row = 0; row < result.rows; ++row)
            {
                size_t aPos = aBase + row * summandOne.rowStride;
                size_t bPos = bBase + row * summandTwo.rowStride;
                size_t cPos = cBase + row * result.rowStride;

                result.data[cPos] = summandOne.data[aPos] + summandTwo.data[bPos];
            }
        }

        return mlt::math::MATH_SUCCESS;
    }
} // namespace mlt::math::kernels
