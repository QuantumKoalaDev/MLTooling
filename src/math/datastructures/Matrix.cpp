#include <mlt/internal/math/datastructures/MatrixStorage.hpp>
#include <mlt/internal/math/datastructures/matrix.hpp>
#include <mlt/internal/math/kernels/MatrixKernel.hpp>
#include <mlt/internal/math/mathstatus.hpp>
#include <mlt/math/Exceptions.hpp>
#include <mlt/math/Matrix.hpp>
#include <mlt/math/Vector.hpp>

#include <memory>
#include <mutex>

using namespace mlt::math::datastructures;
using namespace mlt::math::kernels;
using namespace mlt::core;

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
    mData = std::shared_ptr<void>(
        new MatrixStorage<T>::DataType(),
        [](void* p) { MatrixStorage<T>::del(*static_cast<MatrixStorage<T>::DataType*>(p)); }
    );

    mlt::math::mathStatus createStat =
        MatrixStorage<T>::create(rowCount, colCount, *static_cast<MatrixStorage<T>::DataType*>(mData.get()));

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

template <typename T> Matrix<T>::Matrix(const size_t rowCount, const size_t colCount, std::span<const T> buff)
{
    mData = std::shared_ptr<void>(
        new MatrixStorage<T>::DataType,
        [](void* p) { MatrixStorage<T>::del(*static_cast<MatrixStorage<T>::DataType*>(p)); }
    );

    mlt::math::mathStatus createStat = MatrixStorage<T>::createFromBuff(
        rowCount,
        colCount,
        buff.data(),
        buff.size(),
        *static_cast<MatrixStorage<T>::DataType*>(mData.get())
    );

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

template <typename T>
Matrix<T>::Matrix(
    const size_t startRow, const size_t startCol, const size_t rowCount, const size_t colCount, const size_t rowStride,
    const size_t colStride, std::shared_ptr<void> ptr
)
{
    mData = ptr;

    mView.startRow = startRow;
    mView.startCol = startCol;
    mView.rows = rowCount;
    mView.cols = colCount;
    mView.strideRow = rowStride;
    mView.strideCol = colStride;
}

template <typename T> Matrix<T>& Matrix<T>::operator=(Matrix<T>&& other) noexcept
{
    if (this != &other)
    {
        mData = std::move(other.mData);
        mView = other.mView;
    }

    return *this;
}

template <typename T> Matrix<T>& Matrix<T>::operator=(const Matrix<T>& other) noexcept
{
    if (this != &other)
    {
        mData = other.mData;
        mView = other.mView;
    }

    return *this;
}

template <typename T> const T Matrix<T>::operator[](const size_t row, const size_t col) const
{
    std::shared_lock<std::shared_mutex> lock(mMut);

    size_t pos = MATRIX_COMPUTE_INDEX(row, col);

    return static_cast<MatrixStorage<T>::DataType*>(mData.get())->data[pos];
}

template <typename T> T& Matrix<T>::operator[](const size_t row, const size_t col)
{
    std::unique_lock<std::shared_mutex> lock(mMut);

    size_t pos = MATRIX_COMPUTE_INDEX(row, col);

    return static_cast<MatrixStorage<T>::DataType*>(mData.get())->data[pos];
}

template <typename T> Matrix<T> Matrix<T>::operator+(const Matrix<T>& other) const
{
    if (mView.cols != other.mView.cols || mView.rows != other.mView.rows)
        throw ShapeMismatchException(mView.rows, mView.cols, other.mView.rows, other.mView.cols);

    Matrix<T> resultMat = Matrix(mView.rows, mView.cols);

    typename MatrixKernel<T>::ViewType thisView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(mData.get())->data, mView);

    typename MatrixKernel<T>::ViewType otherView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data, other.mView);

    typename MatrixKernel<T>::ViewType resultView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(resultMat.mData.get())->data, resultMat.mView);

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
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(mData.get())->data, mView);

    typename MatrixKernel<T>::ViewType otherView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data, other.mView);

    mathStatus addStat = MatrixKernel<T>::addInPlace(thisView, otherView);

    if (addStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.cols);

    return *this;
}

template <typename T> Matrix<T> Matrix<T>::operator*(const Matrix<T>& other) const
{
    if (mView.cols != other.mView.rows)
        throw ShapeMismatchException(mView.rows, mView.cols, other.mView.rows, other.mView.cols);

    Matrix<T> resultMat = Matrix(mView.rows, other.mView.cols);

    typename MatrixKernel<T>::ViewType thisView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(mData.get())->data, mView);

    typename MatrixKernel<T>::ViewType otherView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data, other.mView);

    typename MatrixKernel<T>::ViewType resultView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(resultMat.mData.get())->data, resultMat.mView);

    mathStatus multiplyStat = MatrixKernel<T>::multiply(thisView, otherView, resultView);

    if (multiplyStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.cols);

    return resultMat;
}

template <typename T> Vector<T> Matrix<T>::operator*(const Vector<T>& vec) const
{
    const size_t vecCols = vec.isTransposed() ? vec.getLen() : 1;
    const size_t vecRows = vec.isTransposed() ? 1 : vec.getLen();

    if (mView.cols != vecRows)
        throw ShapeMismatchException(mView.rows, mView.cols, vecRows, vecCols);

    Vector<T> resultVec = Vector<T>(mView.rows);
    Matrix<T> vecMat = vec.asMatrix();
    Matrix<T> resultMat = resultVec.asMatrix();

    typename MatrixKernel<T>::ViewType thisView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(mData.get())->data, mView);
    typename MatrixKernel<T>::ViewType vecMatView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(vecMat.mData.get())->data, vecMat.mView);
    typename MatrixKernel<T>::ViewType resultView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(resultMat.mData.get())->data, resultMat.mView);

    mathStatus mulStat = MatrixKernel<T>::multiply(thisView, vecMatView, resultView);

    if (mulStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, vecMatView.rows, vecMatView.cols);

    return resultVec;
}

template <typename T> Shape Matrix<T>::getShape() const
{
    return Shape(mView.rows, mView.cols);
}

template <typename T> Matrix<T> Matrix<T>::clone() const
{
    Matrix<T> distMat = Matrix<T>(mView.rows, mView.cols);

    typename MatrixKernel<T>::ViewType thisView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(mData.get())->data, mView);
    typename MatrixKernel<T>::ViewType distView =
        toInternalView(static_cast<MatrixStorage<T>::DataType*>(distMat.mData.get())->data, distMat.mView);

    mathStatus cloneStat = MatrixKernel<T>::clone(thisView, distView);

    if (cloneStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, distView.rows, distView.cols);

    return distMat;
}

template <typename T>
Matrix<T>
Matrix<T>::submatrix(const size_t rowStart, const size_t colStart, const size_t rowCount, const size_t colCount) const
{
    size_t rowEnd = rowStart + rowCount;
    size_t colEnd = colStart + colCount;

    if (rowStart >= mView.rows || colStart >= mView.cols)
        throw OutOfBoundsException(rowStart, colStart, mView.rows, mView.cols);

    if (rowEnd > mView.rows || colEnd > mView.cols)
        throw OutOfBoundsException(rowEnd, colEnd, mView.rows, mView.cols);

    Matrix<T> subMat = Matrix(*this);

    MatrixView subView = {
        .startCol = colStart,
        .startRow = rowStart,
        .cols = colCount,
        .rows = rowCount,
        .strideCol = mView.strideCol,
        .strideRow = mView.strideRow,
    };

    subMat.mView = subView;

    return subMat;
}

namespace mlt::math::datastructures
{
    template class Matrix<float>;
    template class Matrix<double>;
} // namespace mlt::math::datastructures
