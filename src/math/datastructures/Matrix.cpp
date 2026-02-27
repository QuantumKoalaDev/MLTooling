#include <math/datastructures/matrixview.hpp>
#include "math/mathstatus.hpp"
#include <math/Exceptions.hpp>
#include <math/datastructures/Matrix.hpp>
#include <math/datastructures/matrix.hpp>
#include <math/kernels/matrixkernels.hpp>

#include <math/kernels/MatrixKernel.hpp>

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <type_traits>

using namespace mlt::math::datastructures;
using namespace mlt::math::kernels;

#define MATRIX_COMPUTE_INDEX(row, col)                                                                                 \
    ((col >= mView.cols || row >= mView.rows) ? throw OutOfBoundsException(row, col, mView.rows, mView.cols)           \
                                              : (row * mView.strideRow + col * mView.strideCol +                       \
                                                 mView.startRow * mView.strideRow + mView.startCol * mView.strideCol))

inline MatrixFloatView toInternalView(float* const data, const MatrixView& view)
{
    MatrixFloatView internalView = {
        .data = data + view.startCol * view.strideCol + view.startRow * view.strideRow,
        .rows = view.rows,
        .cols = view.cols,
        .colStride = view.strideCol,
        .rowStride = view.strideRow
    };

    return internalView;
}

inline MatrixDoubleView toInternalView(double* const data, const MatrixView& view)
{
    MatrixDoubleView internalView = {
        .data = data + view.startCol * view.strideCol + view.startRow * view.strideRow,
        .rows = view.rows,
        .cols = view.cols,
        .colStride = view.strideCol,
        .rowStride = view.strideRow
    };

    return internalView;
}

template <typename T> Matrix<T>::~Matrix() = default;

template <typename T> Matrix<T>::Matrix(const size_t rowCount, const size_t colCount)
{
    mlt::math::mathStatus createStat;

    if constexpr (std::is_same_v<T, float>)
    {
        mData =
            std::shared_ptr<void>(new MatrixFloat(), [](void* p) { deleteMatrixFloat(*static_cast<MatrixFloat*>(p)); });
        createStat = createMatrixFloat(rowCount, colCount, *static_cast<MatrixFloat*>(mData.get()));
    }

    if constexpr (std::is_same_v<T, double>)
    {
        mData = std::shared_ptr<void>(
            new MatrixDouble(),
            [](void* p) { deleteMatrixDouble(*static_cast<MatrixDouble*>(p)); }
        );
        createStat = createMatrixDouble(rowCount, colCount, *static_cast<MatrixDouble*>(mData.get()));
    }

    if (createStat != MATH_SUCCESS)
    {
        if (createStat == MATH_ALLOCATION_FAILED)
            throw AllocationFailedException();

        if (createStat == MATH_REQUESTED_ALLOCATION_TO_BIG)
            throw AllocationTooLargeException(sizeof(T), rowCount, colCount);
    }

    mView.rows = rowCount;
    mView.cols = colCount;
    mView.startRow = 0;
    mView.startCol = 0;
    mView.strideCol = rowCount;
    mView.strideRow = 1;
}

template <typename T> Matrix<T>::Matrix(const size_t rowCount, const size_t colCount, std::vector<T> buff)
{
    mlt::math::mathStatus createStat;

    if constexpr (std::is_same_v<T, float>)
    {
        mData =
            std::shared_ptr<void>(new MatrixFloat(), [](void* p) { deleteMatrixFloat(*static_cast<MatrixFloat*>(p)); });
        createStat = createMatrixFloatFromBuff(
            rowCount,
            colCount,
            buff.data(),
            buff.size(),
            *static_cast<MatrixFloat*>(mData.get())
        );
    }

    if constexpr (std::is_same_v<T, double>)
    {
        mData = std::shared_ptr<void>(
            new MatrixDouble(),
            [](void* p) { deleteMatrixDouble(*static_cast<MatrixDouble*>(p)); }
        );
        createStat = createMatrixDoubleFromBuff(
            rowCount,
            colCount,
            buff.data(),
            buff.size(),
            *static_cast<MatrixDouble*>(mData.get())
        );
    }

    if (createStat != MATH_SUCCESS)
    {
        if (createStat == MATH_ALLOCATION_FAILED)
            throw AllocationFailedException();

        if (createStat == MATH_REQUESTED_ALLOCATION_TO_BIG)
            throw AllocationTooLargeException(sizeof(T), rowCount, colCount);
    }

    mView.rows = rowCount;
    mView.cols = colCount;
    mView.startRow = 0;
    mView.startCol = 0;
    mView.strideCol = rowCount;
    mView.strideRow = 1;
}

template <typename T> const T Matrix<T>::operator[](const size_t row, const size_t col) const
{
    std::shared_lock<std::shared_mutex> lock(mMut);

    size_t pos = MATRIX_COMPUTE_INDEX(row, col);

    if constexpr (std::is_same_v<T, float>)
        return static_cast<MatrixFloat*>(mData.get())->data[pos];

    if constexpr (std::is_same_v<T, double>)
        return static_cast<MatrixDouble*>(mData.get())->data[pos];
}

template <typename T> T& Matrix<T>::operator[](const size_t row, const size_t col)
{
    std::unique_lock<std::shared_mutex> lock(mMut);

    size_t pos = MATRIX_COMPUTE_INDEX(row, col);

    if constexpr (std::is_same_v<T, float>)
        return static_cast<MatrixFloat*>(mData.get())->data[pos];

    if constexpr (std::is_same_v<T, double>)
        return static_cast<MatrixDouble*>(mData.get())->data[pos];
}

template <typename T> Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
    if (mView.cols != other.mView.cols || mView.rows != other.mView.rows)
        throw ShapeMismatchException(mView.rows, mView.cols, other.mView.rows, other.mView.cols);

    Matrix<T> resultMat = Matrix(mView.rows, mView.cols);

    typename MatrixKernel<T>::ViewType thisView =
        toInternalView(static_cast<typename MatrixKernel<T>::DataType*>(mData.get())->data, mView);

    typename MatrixKernel<T>::ViewType otherView =
        toInternalView(static_cast<typename MatrixKernel<T>::DataType*>(other.mData.get())->data, other.mView);

    typename MatrixKernel<T>::ViewType resultView =
        toInternalView(static_cast<typename MatrixKernel<T>::DataType*>(resultMat.mData.get())->data, resultMat.mView);

    mathStatus addStat = MatrixKernel<T>::add(thisView, otherView, resultView);

    if (addStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.cols);

    return resultMat;
}

template <typename T> Matrix<T>& Matrix<T>::operator+=(const Matrix<T>& other)
{
    if (mView.cols != other.mView.cols || mView.rows != other.mView.rows)
        throw ShapeMismatchException(mView.rows, mView.cols, other.mView.rows, other.mView.cols);

    typename MatrixKernel<T>::ViewType thisView =
        toInternalView(static_cast<typename MatrixKernel<T>::DataType*>(mData.get())->data, mView);

    typename MatrixKernel<T>::ViewType otherView =
        toInternalView(static_cast<typename MatrixKernel<T>::DataType*>(other.mData.get())->data, other.mView);

    mathStatus addStat = MatrixKernel<T>::addInPlace(thisView, otherView);

    if (addStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.cols);

    return *this;
}

namespace mlt::math::datastructures
{
    template class Matrix<float>;
    template class Matrix<double>;
} // namespace mlt::math::datastructures
