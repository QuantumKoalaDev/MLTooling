#include "mlt/core/ProxyElement.hpp"
#include <mlt/internal/math/datastructures/MatrixStorage.hpp>
#include <mlt/internal/math/kernels/MatrixKernel.hpp>
#include <mlt/internal/math/mathstatus.hpp>
#include <mlt/math/Exceptions.hpp>
#include <mlt/math/Vector.hpp>

#include <memory>
#include <shared_mutex>
#include <utility>

using namespace mlt::math::datastructures;
using namespace mlt::math::kernels;

#define INTERNAL_VIEW(varName, myData, view)                                                                           \
    typename MatrixKernel<T>::ViewType varName = {                                                                     \
        .data = myData + view.start,                                                                                                \
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

    std::shared_lock<std::shared_mutex> mutex(mMut);

    return static_cast<MatrixStorage<T>::DataType*>(mData.get())->data[position];
};

template <typename T> ProxyElement<Vector<T>*, T, 1> Vector<T>::operator[](const size_t position)
{
    if (position >= mView.length)
        throw OutOfBoundsException(1, position, 1, mView.length);

    T* data = static_cast<MatrixStorage<T>::DataType*>(mData.get())->data;
    INTERNAL_VIEW(thisView, data, mView)

    constexpr size_t dim = 1;
    return ProxyElement<Vector<T>*, T, 1>(
        this,
        mMut,
        &Vector<T>::setImpl,
        &Vector<T>::getImpl,
        std::array<size_t, dim>{position + mView.start}
    );
};

template <typename T> Vector<T> Vector<T>::operator+(const Vector& other) const
{
    std::shared_lock<std::shared_mutex> mutex(mMut);

    if (mView.transposed != other.mView.transposed)
    {
        if (mView.transposed)
            throw ShapeMismatchException(1, mView.length, other.mView.length, 1);
        else
            throw ShapeMismatchException(mView.length, 1, 1, other.mView.length);
    }

    if (mView.length != other.mView.length)
    {
        if (!mView.transposed)
            throw ShapeMismatchException(mView.length, 1, other.mView.length, 1);
        else
            throw ShapeMismatchException(1, mView.length, 1, other.mView.length);
    }

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
    {
        bool thisT = mView.transposed;
        bool otherT = other.mView.transposed;

        const size_t rows = thisT ? 1 : mView.length;
        const size_t cols = thisT ? mView.length : 1;
        const size_t otherRows = otherT ? 1 : other.mView.length;
        const size_t otherCols = otherT ? other.mView.length : 1;

        throw ShapeMismatchException(rows, cols, otherRows, otherCols);
    }

    return resultVec;
};

template <typename T> Vector<T> Vector<T>::operator*(const Vector<T>& other) const
{
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
    VectorView subView = {
        len,
        mView.stride,
        mView.start + start,
        mView.transposed
    };

    return subVec;
}

namespace mlt::math::datastructures
{
    template class Vector<float>;
    template class Vector<double>;
} // namespace mlt::math::datastructures
