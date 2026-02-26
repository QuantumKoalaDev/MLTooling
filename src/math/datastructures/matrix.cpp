#include <cstdlib>
#include <math/datastructures/matrix.hpp>
#include <math/mathstatus.hpp>

#include <algorithm>
#include <limits>
#include <new>

namespace mlt::math::datastructures
{
    inline bool overNumericLimit(size_t a, size_t b)
    {
        return a != 0 && b > std::numeric_limits<size_t>::max() / a;
    }

    mathStatus createMatrixFloat(const size_t r, const size_t c, MatrixFloat& out)
    {
        if (overNumericLimit(r, c))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        float* mem = new (std::nothrow) float[c * r]();

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        out.data = mem;
        out.cols = c;
        out.rows = r;
        out.stride = r;

        return MATH_SUCCESS;
    }

    mathStatus createMatrixFloatFromBuff(
        const size_t r, const size_t c, const float* buf, const size_t bufLength, MatrixFloat& out
    )
    {
        if (overNumericLimit(r, c))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        if (r * c != bufLength)
            return MATH_SHAPE_MISSMATCH;

        float* mem = new (std::nothrow) float[bufLength];

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        std::copy(buf, buf + bufLength, mem);

        out.data = mem;
        out.cols = c;
        out.rows = r;
        out.stride = r;

        return MATH_SUCCESS;
    }

    void deleteMatrixFloat(MatrixFloat& mat)
    {
        delete[] mat.data;

        mat.data = nullptr;
        mat.cols = 0;
        mat.rows = 0;
        mat.stride = 0;
    }

    mathStatus resizeMatrixFloat(MatrixFloat& mat, const size_t cSize, const size_t rSize)
    {
        if (overNumericLimit(rSize, cSize))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        float* mem = new (std::nothrow) float[cSize * rSize]();

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        size_t smallC = std::min(mat.cols, cSize);
        size_t smallR = std::min(mat.rows, rSize);

        for (size_t c = 0; c < smallC; ++c)
        {
            float* oldCol = mat.data + c * mat.stride;
            float* newCol = mem + c * cSize;
            std::copy(oldCol, oldCol + smallR, newCol);
        }

        delete[] mat.data;

        mat.data = mem;
        mat.rows = rSize;
        mat.cols = cSize;

        return MATH_SUCCESS;
    }

    mathStatus addRowFloat(const float* row, const size_t rowLength, const size_t atRow, MatrixFloat& mat)
    {
        if (atRow > mat.rows)
            return mlt::math::MATH_MATRIX_OUT_OF_BOUND;

        if (rowLength != mat.cols)
            return MATH_SHAPE_MISSMATCH;

        size_t newRowCount = mat.rows + 1;

        if (overNumericLimit(newRowCount, mat.cols))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        float* mem = new (std::nothrow) float[newRowCount * mat.cols];

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        for (size_t c = 0; c < mat.cols; ++c)
        {
            float* oldCol = mat.data + c * mat.stride;
            float* newCol = mem + c * newRowCount;

            std::copy(oldCol, oldCol + atRow, newCol);
            newCol[atRow] = row[c];
            std::copy(oldCol + atRow, oldCol + mat.rows, newCol + atRow + 1);
        }

        delete[] mat.data;

        mat.data = mem;
        mat.rows = newRowCount;
        mat.stride = newRowCount;

        return MATH_SUCCESS;
    }

    mathStatus addColFloat(const float* col, const size_t colLength, const size_t atCol, MatrixFloat& mat)
    {
        if (atCol > mat.cols)
            return MATH_MATRIX_OUT_OF_BOUND;

        if (colLength != mat.rows)
            return MATH_SHAPE_MISSMATCH;

        size_t newColCount = mat.cols + 1;

        if (overNumericLimit(newColCount, mat.rows))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        float* mem = new (std::nothrow) float[newColCount * mat.rows];

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        for (size_t c = 0; c < atCol; ++c)
        {
            float* oldCol = mat.data + c * mat.stride;
            float* newCol = mem + c * mat.stride;

            std::copy(oldCol, oldCol + mat.stride, newCol);
        }

        std::copy(col, col + colLength, mem + atCol * mat.stride);

        for (size_t c = atCol; c < mat.cols; ++c)
        {
            size_t memPos = c + 1;
            float* oldCol = mat.data + c * mat.stride;
            float* newCol = mem + memPos * mat.rows;

            std::copy(oldCol, oldCol + mat.stride, newCol);
        }

        delete[] mat.data;

        mat.data = mem;
        mat.cols = newColCount;

        return MATH_SUCCESS;
    }

    MatrixFloatView getMatrixFloatView(const MatrixFloat& mat)
    {
        MatrixFloatView
            view{.data = mat.data, .rows = mat.rows, .cols = mat.cols, .colStride = mat.stride, .rowStride = 1};

        return view;
    }

    mathStatus createMatrixDouble(const size_t r, const size_t c, MatrixDouble& out)
    {
        if (overNumericLimit(r, c))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        double* mem = new (std::nothrow) double[r * c]();

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        out.data = mem;
        out.cols = c;
        out.rows = r;
        out.stride = r;

        return MATH_SUCCESS;
    }

    mathStatus createMatrixDoubleFromBuff(
        const size_t r, const size_t c, const double* buff, const size_t buffLength, MatrixDouble& out
    )
    {
        if (overNumericLimit(r, c))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        if (r * c != buffLength)
            return MATH_SHAPE_MISSMATCH;

        double* mem = new (std::nothrow) double[r * c];

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        std::copy(buff, buff + buffLength, mem);

        out.data = mem;
        out.cols = c;
        out.rows = r;
        out.stride = r;

        return MATH_SUCCESS;
    }

    void deleteMatrixDouble(MatrixDouble& mat)
    {
        delete[] mat.data;

        mat.data = nullptr;
        mat.cols = 0;
        mat.rows = 0;
        mat.stride = 0;
    }

    mathStatus resizeMatrixDouble(MatrixDouble& mat, const size_t cSize, const size_t rSize)
    {
        if (overNumericLimit(rSize, cSize))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        double* mem = new (std::nothrow) double[cSize * rSize]();

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        size_t smallC = std::min(mat.cols, cSize);
        size_t smallR = std::min(mat.rows, rSize);

        for (size_t c = 0; c < smallC; ++c)
        {
            double* oldCol = mat.data + c * mat.stride;
            double* newCol = mem + c * cSize;
            std::copy(oldCol, oldCol + smallR, newCol);
        }

        delete[] mat.data;

        mat.data = mem;
        mat.rows = rSize;
        mat.cols = cSize;

        return MATH_SUCCESS;
    }

    mathStatus addRowDouble(const double* row, const size_t rowLength, const size_t atRow, MatrixDouble& mat)
    {
        if (atRow > mat.rows)
            return mlt::math::MATH_MATRIX_OUT_OF_BOUND;

        if (rowLength != mat.cols)
            return MATH_SHAPE_MISSMATCH;

        size_t newRowCount = mat.rows + 1;

        if (overNumericLimit(newRowCount, mat.cols))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        double* mem = new (std::nothrow) double[newRowCount * mat.cols];

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        for (size_t c = 0; c < mat.cols; ++c)
        {
            double* oldCol = mat.data + c * mat.stride;
            double* newCol = mem + c * newRowCount;

            std::copy(oldCol, oldCol + atRow, newCol);
            newCol[atRow] = row[c];
            std::copy(oldCol + atRow, oldCol + mat.rows, newCol + atRow + 1);
        }

        delete[] mat.data;

        mat.data = mem;
        mat.rows = newRowCount;
        mat.stride = newRowCount;

        return MATH_SUCCESS;
    }

    mathStatus addColDouble(const double* col, const size_t colLength, const size_t atCol, MatrixDouble& mat)
    {
        if (atCol > mat.cols)
            return MATH_MATRIX_OUT_OF_BOUND;

        if (colLength != mat.rows)
            return MATH_SHAPE_MISSMATCH;

        size_t newColCount = mat.cols + 1;

        if (overNumericLimit(newColCount, mat.rows))
            return MATH_REQUESTED_ALLOCATION_TO_BIG;

        double* mem = new (std::nothrow) double[newColCount * mat.rows];

        if (!mem)
            return MATH_ALLOCATION_FAILED;

        for (size_t c = 0; c < atCol; ++c)
        {
            double* oldCol = mat.data + c * mat.stride;
            double* newCol = mem + c * mat.stride;

            std::copy(oldCol, oldCol + mat.stride, newCol);
        }

        std::copy(col, col + colLength, mem + atCol * mat.stride);

        for (size_t c = atCol; c < mat.cols; ++c)
        {
            size_t memPos = c + 1;
            double* oldCol = mat.data + c * mat.stride;
            double* newCol = mem + memPos * mat.rows;

            std::copy(oldCol, oldCol + mat.stride, newCol);
        }

        delete[] mat.data;

        mat.data = mem;
        mat.cols = newColCount;

        return MATH_SUCCESS;
    }

    MatrixDoubleView getMatrixFloatView(const MatrixDouble& mat)
    {
        MatrixDoubleView
            view{.data = mat.data, .rows = mat.rows, .cols = mat.cols, .colStride = mat.stride, .rowStride = 1};

        return view;
    }
} // namespace mlt::math::datastructures
