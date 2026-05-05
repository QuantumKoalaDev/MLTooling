#include <cmath>
#include <mlt/internal/math/criticaldef.hpp>
#include <mlt/internal/math/datastructures/matrixview.hpp>
#include <mlt/internal/math/kernels/matrixkernels.hpp>
#include <mlt/internal/math/mathstatus.hpp>

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

    mlt::math::mathStatus addMatrixFloatInPlace(MatrixFloatView& target, const MatrixFloatView& addend)
    {
        if (checkShapeFloat(target, addend) == mlt::math::MATH_SHAPE_MISSMATCH)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        float* RESTRICT aData = addend.data;
        float* RESTRICT cData = target.data;

        for (size_t col = 0; col < target.cols; ++col)
        {
            size_t aBase = col * addend.colStride;
            size_t cBase = col * target.colStride;

            for (size_t row = 0; row < target.rows; ++row)
            {
                size_t aPos = aBase + row * addend.rowStride;
                size_t cPos = cBase + row * target.rowStride;

                cData[cPos] += aData[aPos];
            }
        }

        return mlt::math::MATH_SUCCESS;
    }

    mlt::math::mathStatus addMatrixDoubleInPlace(MatrixDoubleView& target, const MatrixDoubleView& addend)
    {
        if (checkShapeDouble(target, addend) == mlt::math::MATH_SHAPE_MISSMATCH)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        double* RESTRICT aData = addend.data;
        double* RESTRICT cData = target.data;

        for (size_t col = 0; col < target.cols; ++col)
        {
            size_t aBase = col * addend.colStride;
            size_t cBase = col * target.colStride;

            for (size_t row = 0; row < target.rows; ++row)
            {
                size_t aPos = aBase + row * addend.rowStride;
                size_t cPos = cBase + row * target.rowStride;

                cData[cPos] += aData[aPos];
            }
        }

        return mlt::math::MATH_SUCCESS;
    }

    mlt::math::mathStatus subtractMatrixFloat(
        const datastructures::MatrixFloatView& minuend, const datastructures::MatrixFloatView& subtrahend,
        datastructures::MatrixFloatView& difference
    )
    {
        if (checkShapeFloat(minuend, subtrahend))
            return MATH_SHAPE_MISSMATCH;

        if (checkShapeFloat(minuend, difference))
            return MATH_SHAPE_MISSMATCH;

        float* RESTRICT minData = minuend.data;
        float* RESTRICT subData = subtrahend.data;
        float* RESTRICT diffData = difference.data;

        for (size_t col = 0; col < minuend.cols; ++col)
        {
            size_t minBase = col * minuend.colStride;
            size_t subBase = col * subtrahend.colStride;
            size_t diffBase = col * difference.colStride;

            for (size_t row = 0; row < minuend.rows; ++row)
            {
                size_t minPos = minBase + row * minuend.rowStride;
                size_t subPos = subBase + row * subtrahend.rowStride;
                size_t diffPos = diffBase + row * difference.rowStride;

                diffData[diffPos] = minData[minPos] - subData[subPos];
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus subtractMatrixDouble(
        const datastructures::MatrixDoubleView& minuend, const datastructures::MatrixDoubleView& subtrahend,
        datastructures::MatrixDoubleView& difference
    )
    {
        if (checkShapeDouble(minuend, subtrahend))
            return MATH_SHAPE_MISSMATCH;

        if (checkShapeDouble(minuend, difference))
            return MATH_SHAPE_MISSMATCH;

        double* RESTRICT minData = minuend.data;
        double* RESTRICT subData = subtrahend.data;
        double* RESTRICT diffData = difference.data;

        for (size_t col = 0; col < minuend.cols; ++col)
        {
            size_t minBase = col * minuend.colStride;
            size_t subBase = col * subtrahend.colStride;
            size_t diffBase = col * difference.colStride;

            for (size_t row = 0; row < minuend.rows; ++row)
            {
                size_t minPos = minBase + row * minuend.rowStride;
                size_t subPos = subBase + row * subtrahend.rowStride;
                size_t diffPos = diffBase + row * difference.rowStride;

                diffData[diffPos] = minData[minPos] - subData[subPos];
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus subtractInPlaceMatrixFloat(
        datastructures::MatrixFloatView& difference, const datastructures::MatrixFloatView& subtrahend
    )
    {
        if (checkShapeFloat(difference, subtrahend))
            return MATH_SHAPE_MISSMATCH;

        float* RESTRICT diffData = difference.data;
        float* RESTRICT subData = subtrahend.data;

        for (size_t col = 0; col < difference.cols; ++col)
        {
            size_t diffBase = col * difference.colStride;
            size_t subBase = col * subtrahend.colStride;

            for (size_t row = 0; row < difference.rows; ++row)
            {
                size_t diffPos = diffBase + row * difference.rowStride;
                size_t subPos = subBase + row * subtrahend.rowStride;

                diffData[diffPos] -= subData[subPos];
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus subtractInPlaceMatrixDouble(
        datastructures::MatrixDoubleView& difference, const datastructures::MatrixDoubleView& subtrahend
    )
    {
        if (checkShapeDouble(difference, subtrahend))
            return MATH_SHAPE_MISSMATCH;

        double* RESTRICT diffData = difference.data;
        double* RESTRICT subData = subtrahend.data;

        for (size_t col = 0; col < difference.cols; ++col)
        {
            size_t diffBase = col * difference.colStride;
            size_t subBase = col * subtrahend.colStride;

            for (size_t row = 0; row < difference.rows; ++row)
            {
                size_t diffPos = diffBase + row * difference.rowStride;
                size_t subPos = subBase + row * subtrahend.rowStride;

                diffData[diffPos] -= subData[subPos];
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus multiplyMatrixFloat(
        const datastructures::MatrixFloatView& multiplicant, const datastructures::MatrixFloatView& multiplier,
        datastructures::MatrixFloatView& product
    )
    {
        if (multiplicant.cols != multiplier.rows)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        if (product.rows != multiplicant.rows || product.cols != multiplier.cols)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        float* RESTRICT aData = multiplicant.data;
        float* RESTRICT bData = multiplier.data;
        float* RESTRICT cData = product.data;

        for (size_t colC = 0; colC < product.cols; ++colC)
        {
            size_t cBase = colC * product.colStride;
            size_t bBase = colC * multiplier.colStride;

            for (size_t rowC = 0; rowC < product.rows; ++rowC)
            {
                size_t posC = cBase + rowC * product.rowStride;
                size_t aBase = rowC * multiplicant.rowStride;

                float sum = 0.f;

                for (size_t colA = 0; colA < multiplicant.cols; ++colA)
                {
                    size_t aPos = aBase + colA * multiplicant.colStride;
                    size_t bPos = bBase + colA * multiplier.rowStride;
                    // C[rowC, colC] += A[rowC, colA] * B[colA, colC];
                    sum += aData[aPos] * bData[bPos];
                }

                cData[posC] = sum;
            }
        }

        return mlt::math::MATH_SUCCESS;
    }

    mlt::math::mathStatus multiplyMatrixDouble(
        const datastructures::MatrixDoubleView& multiplicant, const datastructures::MatrixDoubleView& multiplier,
        datastructures::MatrixDoubleView& product
    )
    {
        if (multiplicant.cols != multiplier.rows)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        if (product.rows != multiplicant.rows || product.cols != multiplier.cols)
            return mlt::math::MATH_SHAPE_MISSMATCH;

        double* RESTRICT aData = multiplicant.data;
        double* RESTRICT bData = multiplier.data;
        double* RESTRICT cData = product.data;

        for (size_t colC = 0; colC < product.cols; ++colC)
        {
            size_t cBase = colC * product.colStride;
            size_t bBase = colC * multiplier.colStride;

            for (size_t rowC = 0; rowC < product.rows; ++rowC)
            {
                size_t posC = cBase + rowC * product.rowStride;
                size_t aBase = rowC * multiplicant.rowStride;

                double sum = 0.0;

                for (size_t colA = 0; colA < multiplicant.cols; ++colA)
                {
                    size_t aPos = aBase + colA * multiplicant.colStride;
                    size_t bPos = bBase + colA * multiplier.rowStride;

                    sum += aData[aPos] * bData[bPos];
                }

                cData[posC] = sum;
            }
        }

        return mlt::math::MATH_SUCCESS;
    }

    mlt::math::mathStatus
    cloneMatrixFloat(const datastructures::MatrixFloatView& src, datastructures::MatrixFloatView& dist)
    {
        if (src.cols != dist.cols || src.rows != dist.rows)
            return MATH_SHAPE_MISSMATCH;

        float* RESTRICT srcData = src.data;
        float* RESTRICT distData = dist.data;

        for (size_t col = 0; col < dist.cols; ++col)
        {
            size_t srcBase = col * src.colStride;
            size_t distBase = col * dist.colStride;

            for (size_t row = 0; row < dist.rows; ++row)
            {
                size_t srcPos = srcBase + row * src.rowStride;
                size_t distPos = distBase + row * dist.rowStride;

                distData[distPos] = srcData[srcPos];
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus
    cloneMatrixDouble(const datastructures::MatrixDoubleView& src, datastructures::MatrixDoubleView& dist)
    {
        if (src.cols != dist.cols || src.rows != dist.rows)
            return MATH_SHAPE_MISSMATCH;

        double* RESTRICT srcData = src.data;
        double* RESTRICT distData = dist.data;

        for (size_t col = 0; col < dist.cols; ++col)
        {
            size_t srcBase = col * src.colStride;
            size_t distBase = col * dist.colStride;

            for (size_t row = 0; row < dist.rows; ++row)
            {
                size_t srcPos = srcBase + row * src.rowStride;
                size_t distPos = distBase + row * dist.rowStride;

                distData[distPos] = srcData[srcPos];
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus multiplyScalarMatrixFloat(
        const datastructures::MatrixFloatView& mat, const float scalar, datastructures::MatrixFloatView& result
    )
    {
        if ((mat.rows * mat.cols) != (result.rows * result.cols))
            return MATH_SHAPE_MISSMATCH;

        float* RESTRICT matData = mat.data;
        float* RESTRICT resultData = result.data;

        for (size_t col = 0; col < mat.cols; ++col)
        {
            size_t matBase = col * mat.colStride;
            size_t resultBase = col * result.colStride;

            for (size_t row = 0; row < mat.rows; ++row)
            {
                size_t matPos = matBase + row * mat.rowStride;
                size_t resultPos = resultBase + row * result.rowStride;

                resultData[resultPos] = matData[matPos] * scalar;
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus multiplyScalarMatrixDouble(
        const datastructures::MatrixDoubleView& mat, const double scalar, datastructures::MatrixDoubleView& result
    )
    {
        if ((mat.rows * mat.cols) != (result.rows * result.cols))
            return MATH_SHAPE_MISSMATCH;

        double* RESTRICT matData = mat.data;
        double* RESTRICT resultData = result.data;

        for (size_t col = 0; col < mat.cols; ++col)
        {
            size_t matBase = col * mat.colStride;
            size_t resultBase = col * result.colStride;

            for (size_t row = 0; row < mat.rows; ++row)
            {
                size_t matPos = matBase + row * mat.rowStride;
                size_t resPos = resultBase + row * result.rowStride;

                resultData[resPos] = matData[matPos] * scalar;
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus multiplyScalarMatrixFloatInPlace(datastructures::MatrixFloatView& mat, float scalar)
    {
        float* RESTRICT matData = mat.data;

        for (size_t col = 0; col < mat.cols; ++col)
        {
            size_t matBase = col * mat.colStride;

            for (size_t row = 0; row < mat.rows; ++row)
            {
                size_t matPos = matBase + row * mat.rowStride;
                matData[matPos] *= scalar;
            }
        }

        return MATH_SUCCESS;
    }

    mlt::math::mathStatus multiplyScalarMatrixDoubleInPlace(datastructures::MatrixDoubleView& mat, double scalar)
    {
        double* RESTRICT matData = mat.data;

        for (size_t col = 0; col < mat.cols; ++col)
        {
            size_t matBase = col * mat.colStride;

            for (size_t row = 0; row < mat.rows; ++row)
            {
                size_t matPos = matBase + row * mat.rowStride;
                matData[matPos] *= scalar;
            }
        }

        return MATH_SUCCESS;
    }

} // namespace mlt::math::kernels
