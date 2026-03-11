#include "math/Exceptions.hpp"
#include <mlt/math/matrix.h>

#include <Math.hpp>

#ifdef __cplusplus
extern "C"
{

    using namespace mlt::math::datastructures;

    struct mltMatrixF
    {
        Matrix<float> implMat;

        mltMatrixF(size_t rows, size_t cols) : implMat(rows, cols) {}
        mltMatrixF(size_t rows, size_t cols, std::span<const float> buff) : implMat(rows, cols, buff) {}
        mltMatrixF(Matrix<float>&& mat) : implMat(mat) {}
    };

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFCreate(size_t rows, size_t cols, mltMatrixF** out)
    {
        if (!out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            *out = new mltMatrixF(rows, cols);
        }
        catch (mlt::math::AllocationFailedException)
        {
            return MLT_STATUS_ALLOCATION_FAILED;
        }
        catch (mlt::math::AllocationTooLargeException)
        {
            return MLT_STATUS_ALLOCATION_TOO_LARGE;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFCreateFromBuff(
        const size_t rows, const size_t cols, const float* buff, size_t buffSize, mltMatrixF** out
    )
    {
        if (!buff || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            *out = new mltMatrixF(rows, cols, std::span<const float>(buff, buffSize));
        }
        catch (mlt::math::AllocationFailedException)
        {
            return MLT_STATUS_ALLOCATION_FAILED;
        }
        catch (mlt::math::AllocationTooLargeException)
        {
            return MLT_STATUS_ALLOCATION_TOO_LARGE;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFDestroy(mltMatrixF* mat)
    {
        if (!mat)
            return MLT_STATUS_ERR_NULL_PTR;

        delete mat;

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFGet(const mltMatrixF* mat, const size_t row, size_t col, float* out)
    {
        if (!mat || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            *out = mat->implMat[row, col];
        }
        catch (mlt::math::OutOfBoundsException)
        {
            return MLT_STATUS_OUT_OF_BOUNDS;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFSet(mltMatrixF* mat, const size_t row, const size_t col, float val)
    {
        if (!mat)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            mat->implMat[row, col] = val;
        }
        catch (mlt::math::OutOfBoundsException)
        {
            return MLT_STATUS_OUT_OF_BOUNDS;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFRowCount(const mltMatrixF* mat, size_t* out)
    {
        if (!mat)
            return MLT_STATUS_ERR_NULL_PTR;

        *out = mat->implMat.getShape().rows;

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFColCount(const mltMatrixF* mat, size_t* out)
    {
        if (!mat)
            return MLT_STATUS_ERR_NULL_PTR;

        *out = mat->implMat.getShape().cols;

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFAdd(const mltMatrixF* a, const mltMatrixF* b, mltMatrixF** out)
    {
        if (!a || !b || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        mltMatrixF* mat = NULL;

        try
        {
            Matrix<float> C = a->implMat + b->implMat;
            *out = new mltMatrixF(std::move(C));
        }
        catch (mlt::math::AllocationFailedException)
        {
            return MLT_STATUS_ALLOCATION_FAILED;
        }
        catch (mlt::math::AllocationTooLargeException)
        {
            return MLT_STATUS_ALLOCATION_TOO_LARGE;
        }
        catch (mlt::math::ShapeMismatchException)
        {
            return MLT_STATUS_SHAPE_MISMATCH;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFAddInPlace(mltMatrixF* a, const mltMatrixF* b)
    {
        if (!a || !b)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            a->implMat += b->implMat;
        }
        catch (mlt::math::ShapeMismatchException)
        {
            return MLT_STATUS_SHAPE_MISMATCH;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFMultiply(const mltMatrixF* a, const mltMatrixF* b, mltMatrixF** out)
    {
        if (!a || !b || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<float> C = a->implMat * b->implMat;
            *out = new mltMatrixF(std::move(C));
        }
        catch (mlt::math::AllocationFailedException)
        {
            return MLT_STATUS_ALLOCATION_FAILED;
        }
        catch (mlt::math::AllocationTooLargeException)
        {
            return MLT_STATUS_ALLOCATION_TOO_LARGE;
        }
        catch (mlt::math::ShapeMismatchException)
        {
            return MLT_STATUS_SHAPE_MISMATCH;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFClone(const mltMatrixF* mat, mltMatrixF** out)
    {
        if (!mat || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<float> clonedMat = mat->implMat.clone();
            *out = new mltMatrixF(std::move(clonedMat));
        }
        catch (mlt::math::AllocationFailedException)
        {
            return MLT_STATUS_ALLOCATION_FAILED;
        }
        catch (mlt::math::AllocationTooLargeException)
        {
            return MLT_STATUS_ALLOCATION_TOO_LARGE;
        }
        catch (mlt::math::ShapeMismatchException)
        {
            return MLT_STATUS_SHAPE_MISMATCH;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFCopy(const mltMatrixF* mat, mltMatrixF** out)
    {
        if (!mat || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<float> copyMat = Matrix(mat->implMat);
            *out = new mltMatrixF(std::move(copyMat));
        }
        catch (mlt::math::AllocationFailedException)
        {
            return MLT_STATUS_ALLOCATION_FAILED;
        }
        catch (mlt::math::AllocationTooLargeException)
        {
            return MLT_STATUS_ALLOCATION_TOO_LARGE;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFSubmatrix(
        const mltMatrixF* mat, size_t startRow, size_t startCol, size_t rowCount, size_t colCount, mltMatrixF** out
    )
    {
        if (!mat || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<float> submatrix = mat->implMat.submatrix(startRow, startCol, rowCount, colCount);
            *out = new mltMatrixF(std::move(submatrix));
        }
        catch (mlt::math::AllocationFailedException)
        {
            return MLT_STATUS_ALLOCATION_FAILED;
        }
        catch (mlt::math::AllocationTooLargeException)
        {
            return MLT_STATUS_ALLOCATION_TOO_LARGE;
        }
        catch (mlt::math::OutOfBoundsException)
        {
            return MLT_STATUS_OUT_OF_BOUNDS;
        }
        catch (...)
        {
            return MLT_STATUS_INTERNAL_ERROR;
        }

        return MLT_STATUS_SUCCESS;
    }
}
#endif
