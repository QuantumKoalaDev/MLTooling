#include <cstddef>
#include <mlt/internal/math/datastructures/MatrixStorage.hpp>
#include <mlt/internal/math/kernels/MatrixKernel.hpp>
#include <mlt/internal/math/kernels/VectorKernel.hpp>
#include <mlt/internal/math/mathstatus.hpp>
#include <mlt/math/Exceptions.hpp>
#include <mlt/math/Vector.hpp>

#include <memory>
#include <utility>

using namespace mlt::math::datastructures;
using namespace mlt::math::kernels;

#define INTERNAL_VIEW(varName, myData, view)                                                                           \
    typename MatrixKernel<T>::ViewType varName = {                                                                     \
        .data = myData + view.start,                                                                                   \
        .rows = view.transposed ? 1 : view.length,                                                                     \
        .cols = view.transposed ? view.length : 1,                                                                     \
        .colStride = view.transposed ? view.stride : 1,                                                                \
        .rowStride = view.transposed ? 1 : view.stride,                                                                \
    };

template <typename T> T Vector<T>::getImpl(Vector<T>* vec, const std::array<size_t, 1>& dimArray)
{
    const bool isTransposed = vec->mView.transposed;

    const size_t row = isTransposed ? 0 : dimArray[0];
    const size_t col = isTransposed ? dimArray[0] : 0;

    T* data = static_cast<MatrixStorage<T>::DataType*>(vec->mData.get())->data;
    INTERNAL_VIEW(view, data, vec->mView)
    T val = 0;
    const mathStatus stat = MatrixKernel<T>::get(row, col, view, val);

    if (stat == MATH_MATRIX_OUT_OF_BOUND)
        throw OutOfBoundsException(row, col, view.rows, view.cols);

    return val;
}

template <typename T> void Vector<T>::setImpl(Vector<T>* vec, const std::array<size_t, 1>& dimArray, T val)
{
    const bool isTransposed = vec->mView.transposed;

    const size_t row = isTransposed ? 0 : dimArray[0];
    const size_t col = isTransposed ? dimArray[0] : 0;
    T* data = static_cast<MatrixStorage<T>::DataType*>(vec->mData.get())->data;
    INTERNAL_VIEW(view, data, vec->mView);

    const mathStatus stat = MatrixKernel<T>::set(row, col, view, val);

    if (stat == MATH_MATRIX_OUT_OF_BOUND)
        throw OutOfBoundsException(row, col, view.rows, view.cols);
}

template <typename T> void Vector<T>::checkShape(const Vector<T>& other) const
{
    constexpr size_t minRowCol = 1;

    if (mView.transposed != other.mView.transposed)
    {
        if (mView.transposed)
            throw ShapeMismatchException(minRowCol, mView.length, other.mView.length, minRowCol);
        throw ShapeMismatchException(mView.length, minRowCol, minRowCol, other.mView.length);
    }

    if (mView.length != other.mView.length)
    {
        if (!mView.transposed)
            throw ShapeMismatchException(mView.length, minRowCol, other.mView.length, minRowCol);
        throw ShapeMismatchException(minRowCol, mView.length, minRowCol, other.mView.length);
    }
}

template <typename T> Vector<T>::~Vector() = default;

template <typename T> Vector<T>::Vector(const size_t size)
{
    mData = std::shared_ptr<void>(
        new MatrixStorage<T>::DataType(),
        [](void* p) { MatrixStorage<T>::del(*static_cast<MatrixStorage<T>::DataType*>(p)); }
    );

    const mathStatus createStat =
        MatrixStorage<T>::create(1, size, *static_cast<MatrixStorage<T>::DataType*>(mData.get()));

    if (createStat != MATH_SUCCESS)
    {
        if (createStat == MATH_ALLOCATION_FAILED)
            throw AllocationFailedException();

        if (createStat == MATH_REQUESTED_ALLOCATION_TO_BIG)
            throw AllocationTooLargeException(sizeof(T), 1, size);
    }

    mView.length = size;
    mView.stride = 1;
    mView.transposed = false;
    mView.start = 0;
};

template <typename T> Vector<T>::Vector(std::span<const T> buff)
{
    mData = std::shared_ptr<void>(
        new MatrixStorage<T>::DataType(),
        [](void* p) { MatrixStorage<T>::del(*static_cast<MatrixStorage<T>::DataType*>(p)); }
    );

    mlt::math::mathStatus createStat = MatrixStorage<T>::createFromBuff(
        1,
        buff.size(),
        buff.data(),
        buff.size(),
        *static_cast<MatrixStorage<T>::DataType*>(mData.get())
    );

    if (createStat != MATH_SUCCESS)
    {
        if (createStat == MATH_ALLOCATION_FAILED)
            throw AllocationFailedException();

        if (createStat == MATH_REQUESTED_ALLOCATION_TO_BIG)
            throw AllocationTooLargeException(sizeof(T), 1, buff.size());
    }

    mView.length = buff.size();
    mView.stride = 1;
    mView.transposed = false;
    mView.start = 0;
};

template <typename T> Vector<T>& Vector<T>::operator=(const Vector<T>& other) noexcept
{
    if (this != &other)
    {
        mData = other.mData;
        mView = other.mView;
    }

    return *this;
};

template <typename T> Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
    if (this != &other)
    {
        mData = std::move(other.mData);
        mView = other.mView;
    }

    return *this;
};

template <typename T> T Vector<T>::operator[](const size_t position) const
{
    if (position >= mView.length)
        throw OutOfBoundsException(1, position, 1, mView.length);

    return static_cast<MatrixStorage<T>::DataType*>(mData.get())->data[mView.start + position * mView.stride];
};

template <typename T> T& Vector<T>::operator[](const size_t position)
{
    if (position >= mView.length)
        throw OutOfBoundsException(1, position, 1, mView.length);

    return static_cast<MatrixStorage<T>::DataType*>(mData.get())->data[mView.start + position * mView.stride];
};

template <typename T> Vector<T> Vector<T>::operator+(const Vector& other) const
{
    return add(other);
};

template <typename T> Vector<T>& Vector<T>::operator+=(const Vector<T>& other)
{
    return addInPlace(other);
}

template <typename T> Vector<T> Vector<T>::operator-(const Vector& other) const
{
    return subtract(other);
}

template <typename T> Vector<T>& Vector<T>::operator-=(const Vector<T>& other)
{
    return subtractInPlace(other);
}

template <typename T> Vector<T> Vector<T>::operator*(const T scalar) const
{
    return mulScalar(scalar);
}

template <typename T> Vector<T>& Vector<T>::operator*=(const T scalar)
{
    return mulScalarInPlace(scalar);
}

template <typename T> Vector<T> Vector<T>::add(const Vector<T>& other) const
{
    checkShape(other);

    Vector<T> resultVec = Vector(mView.length);
    resultVec.mView.transposed = mView.transposed;

    T* thisData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    T* otherData = static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data;
    T* resultData = static_cast<MatrixStorage<T>::DataType*>(resultVec.mData.get())->data;

    INTERNAL_VIEW(thisView, thisData, mView)
    INTERNAL_VIEW(otherView, otherData, other.mView)
    INTERNAL_VIEW(resultView, resultData, resultVec.mView)

    const mathStatus addStat = MatrixKernel<T>::add(thisView, otherView, resultView);

    if (addStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.cols);

    return resultVec;
}

template <typename T> Vector<T>& Vector<T>::addInPlace(const Vector<T>& other)
{
    checkShape(other);

    T* thisData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    T* otherData = static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data;

    INTERNAL_VIEW(thisView, thisData, mView)
    INTERNAL_VIEW(otherView, otherData, other.mView)

    mathStatus addStat = MatrixKernel<T>::addInPlace(thisView, otherView);

    if (addStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.cols);

    return *this;
}

template <typename T> Vector<T> Vector<T>::subtract(const Vector<T>& other) const
{
    checkShape(other);

    Vector<T> resultVec = Vector(mView.length);

    T* thisData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    T* otherData = static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data;
    T* resultData = static_cast<MatrixStorage<T>::DataType*>(resultVec.mData.get())->data;

    INTERNAL_VIEW(thisView, thisData, mView)
    INTERNAL_VIEW(otherView, otherData, other.mView)
    INTERNAL_VIEW(resultView, resultData, resultVec.mView)

    mathStatus subStat = MatrixKernel<T>::subtract(thisView, otherView, resultView);

    if (subStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.cols);

    return resultVec;
}

template <typename T> Vector<T>& Vector<T>::subtractInPlace(const Vector<T>& other)
{
    checkShape(other);

    T* thisData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    T* otherData = static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data;

    INTERNAL_VIEW(thisView, thisData, mView)
    INTERNAL_VIEW(otherView, otherData, other.mView)

    mathStatus subStat = MatrixKernel<T>::subtractInPlace(thisView, otherView);

    if (subStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.cols);

    return *this;
}

template <typename T> Vector<T> Vector<T>::mulScalar(const T scalar) const
{
    Vector<T> resultVec = Vector(mView.length);
    resultVec.mView.transposed = mView.transposed;

    T* thisData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    T* resData = static_cast<MatrixStorage<T>::DataType*>(resultVec.mData.get())->data;

    INTERNAL_VIEW(thisView, thisData, mView)
    INTERNAL_VIEW(resView, resData, resultVec.mView)

    mathStatus mulStat = MatrixKernel<T>::multiplyScalar(thisView, scalar, resView);

    if (mulStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, resView.rows, resView.cols);

    return resultVec;
}

template <typename T> Vector<T>& Vector<T>::mulScalarInPlace(const T scalar)
{
    T* thisData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    INTERNAL_VIEW(thisView, thisData, mView)

    mathStatus mulStat = MatrixKernel<T>::multiplyScalarInPlace(thisView, scalar);

    return *this;
}

template <typename T> T Vector<T>::dot(const Vector<T>& other) const
{
    T* thisData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    T* otherData = static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data;

    INTERNAL_VIEW(thisView, thisData, mView)
    INTERNAL_VIEW(otherView, otherData, other.mView)

    if (mView.length != other.mView.length || mView.transposed != other.mView.transposed)
        throw ShapeMismatchException(thisView.rows, thisView.cols, otherView.rows, otherView.rows);

    return VectorKernel<T>::dot(thisData, mView.length, mView.stride, otherData, other.mView.stride);
}

template <typename T> Vector<T> Vector<T>::hadamard(const Vector& other) const
{
    Vector<T> result = clone();

    T* resultData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    T* otherData = static_cast<MatrixStorage<T>::DataType*>(other.mData.get())->data;

    INTERNAL_VIEW(resultView, resultData, mView)
    INTERNAL_VIEW(otherView, otherData, other.mView)

    if (result.mView.length != other.mView.length || result.mView.transposed != other.mView.transposed)
        throw ShapeMismatchException(resultView.rows, resultView.cols, otherView.rows, otherView.rows);

    VectorKernel<T>::hadamard(resultData, result.mView.length, result.mView.stride, otherData, other.mView.stride);

    return result;
}

template <typename T> size_t Vector<T>::getLen() const
{
    return mView.length;
}

template <typename T> bool Vector<T>::isTransposed() const
{
    return mView.transposed;
}

template <typename T> void Vector<T>::transpose()
{
    mView.transposed = !mView.transposed;
}

template <typename T> Vector<T> Vector<T>::clone() const
{
    Vector<T> distVec = Vector<T>(mView.length);

    T* thisData = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    T* distData = static_cast<MatrixStorage<T>::DataType*>(distVec.mData.get())->data;
    INTERNAL_VIEW(thisView, thisData, mView)
    INTERNAL_VIEW(distView, distData, distVec.mView)

    mathStatus cloneStat = MatrixKernel<T>::clone(thisView, distView);

    if (cloneStat == MATH_SHAPE_MISSMATCH)
        throw ShapeMismatchException(thisView.rows, thisView.cols, distView.rows, distView.cols);

    return distVec;
}

template <typename T> Vector<T> Vector<T>::subvector(const size_t start, const size_t len) const
{
    constexpr size_t minRowCol = 1;
    const bool transposed = mView.transposed;
    const size_t end = start + len;

    if (start >= mView.length)
        throw OutOfBoundsException(start, minRowCol, mView.length, minRowCol);

    if (end >= mView.length)
        throw OutOfBoundsException(end, minRowCol, mView.length, minRowCol);

    Vector<T> subVec = Vector(*this);
    VectorView subView = {len, mView.stride, mView.start + start, mView.transposed};

    return subVec;
}

template <typename T> Matrix<T> Vector<T>::asMatrix() const
{
    const size_t startRows = mView.transposed ? 0 : mView.start;
    const size_t startCols = mView.transposed ? mView.start : 0;
    const size_t rows = mView.transposed ? 1 : mView.length;
    const size_t cols = mView.transposed ? mView.length : 1;
    const size_t rowStride = mView.transposed ? 1 : mView.stride;
    const size_t colStride = mView.transposed ? mView.stride : 1;

    return Matrix<T>(startCols, startRows, rows, cols, rowStride, colStride, mData);
}

namespace mlt::math::datastructures
{
    template class Vector<float>;
    template class Vector<double>;
} // namespace mlt::math::datastructures
