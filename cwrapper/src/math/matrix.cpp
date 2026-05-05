#include <atomic>
#include <mlt/Math.hpp>
#include <mlt/math/Exceptions.hpp>
#include <mlt/math/Matrix.hpp>
#include <mlt/math/matrix.h>

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

    struct mltMatrixD
    {
        Matrix<double> implMat;

        mltMatrixD(size_t rows, size_t cols) : implMat(rows, cols) {}
        mltMatrixD(size_t rows, size_t cols, std::span<const double> buff) : implMat(rows, cols, buff) {}
        mltMatrixD(Matrix<double>&& mat) : implMat(mat) {}
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

        try
        {
            Matrix<float> C = a->implMat.add(b->implMat);
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
            a->implMat.addInPlace(b->implMat);
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
            Matrix<float> C = a->implMat.multiply(b->implMat);
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDCreate(size_t rows, size_t cols, mltMatrixD** out)
    {
        if (!out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            *out = new mltMatrixD(rows, cols);
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDCreateFromBuff(
        const size_t rows, const size_t cols, const double* buff, size_t buffSize, mltMatrixD** out
    )
    {
        if (!buff || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            *out = new mltMatrixD(rows, cols, std::span<const double>(buff, buffSize));
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDDestroy(mltMatrixD* mat)
    {
        if (!mat)
            return MLT_STATUS_ERR_NULL_PTR;

        delete mat;

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDGet(const mltMatrixD* mat, const size_t row, size_t col, double* out)
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDSet(mltMatrixD* mat, const size_t row, const size_t col, double val)
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDRowCount(const mltMatrixD* mat, size_t* out)
    {
        if (!mat)
            return MLT_STATUS_ERR_NULL_PTR;

        *out = mat->implMat.getShape().rows;

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDColCount(const mltMatrixD* mat, size_t* out)
    {
        if (!mat)
            return MLT_STATUS_ERR_NULL_PTR;

        *out = mat->implMat.getShape().cols;

        return MLT_STATUS_SUCCESS;
    }

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDAdd(const mltMatrixD* a, const mltMatrixD* b, mltMatrixD** out)
    {
        if (!a || !b || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<double> C = a->implMat.add(b->implMat);
            *out = new mltMatrixD(std::move(C));
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDAddInPlace(mltMatrixD* a, const mltMatrixD* b)
    {
        if (!a || !b)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            a->implMat.addInPlace(b->implMat);
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDMultiply(const mltMatrixD* a, const mltMatrixD* b, mltMatrixD** out)
    {
        if (!a || !b || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<double> C = a->implMat.multiply(b->implMat);
            *out = new mltMatrixD(std::move(C));
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDClone(const mltMatrixD* mat, mltMatrixD** out)
    {
        if (!mat || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<double> clonedMat = mat->implMat.clone();
            *out = new mltMatrixD(std::move(clonedMat));
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDCopy(const mltMatrixD* mat, mltMatrixD** out)
    {
        if (!mat || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<double> copyMat = Matrix(mat->implMat);
            *out = new mltMatrixD(std::move(copyMat));
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

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixDSubmatrix(
        const mltMatrixD* mat, size_t startRow, size_t startCol, size_t rowCount, size_t colCount, mltMatrixD** out
    )
    {
        if (!mat || !out)
            return MLT_STATUS_ERR_NULL_PTR;

        try
        {
            Matrix<double> submatrix = mat->implMat.submatrix(startRow, startCol, rowCount, colCount);
            *out = new mltMatrixD(std::move(submatrix));
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
