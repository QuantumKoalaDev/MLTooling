#include "mlt/internal/math/mathstatus.hpp"
#include <mlt/math/Vector.hpp>
#include <mlt/math/Exceptions.hpp>
#include <mlt/internal/math/datastructures/MatrixStorage.hpp>
#include <mlt/internal/math/kernels/MatrixKernel.hpp>

#include <memory>
#include <mutex>
#include <shared_mutex>
#include <utility>

using namespace mlt::math::datastructures;
using namespace mlt::math::kernels;

template <typename T> Vector<T>::~Vector() = default;

template <typename T> Vector<T>::Vector(const size_t length)
{
    mData = std::shared_ptr<void>(
        new MatrixStorage<T>::DataType(),
        [](void* p) { MatrixStorage<T>::del(*static_cast<MatrixStorage<T>::DataType*>(p)); }
    );

    mlt::math::mathStatus createStat = MatrixStorage<T>::create(1, length, *static_cast<MatrixStorage<T>::DataType*>(mData.get()));

    if (createStat != MATH_SUCCESS)
    {
        if (createStat == MATH_ALLOCATION_FAILED)
            throw AllocationFailedException();

        if (createStat == MATH_REQUESTED_ALLOCATION_TO_BIG)
            throw AllocationTooLargeException(sizeof(T), 1, length);
    }

    mView.startPos = 0;
    mView.length = length;
    mView.stride = 1;
    mView.transposed = false;
};

template <typename T> Vector<T>::Vector(const size_t length, std::span<const T> buff)
{
    mData = std::shared_ptr<void>(
        new MatrixStorage<T>::DataType(),
        [](void* p) { MatrixStorage<T>::del(*static_cast<MatrixStorage<T>::DataType*>(p)); }
    );

    mlt::math::mathStatus createStat = MatrixStorage<T>::createFromBuff(
        1,
        length,
        buff.data(),
        buff.size(),
        *static_cast<MatrixStorage<T>::DataType*>(mData.get())
    );

    if (createStat != MATH_SUCCESS)
    {
        if (createStat == MATH_ALLOCATION_FAILED)
            throw AllocationFailedException();

        if (createStat == MATH_REQUESTED_ALLOCATION_TO_BIG)
            throw AllocationTooLargeException(sizeof(T), 1, length);
    }
    
    mView.startPos = 0;
    mView.length = length;
    mView.stride = 1;
    mView.transposed = false;
};

template <typename T> Vector<T>& Vector<T>::operator=(const Vector<T>& other) noexcept
{
    if (this != other)
    {
        mData = other.mData;
        mView = other.mView;
    }

    return *this;
};

template <typename T> Vector<T>& Vector<T>::operator=(Vector<T>&& other) noexcept
{
    if (this != other)
    {
        mData = std::move(other.mData);
        mView = other.mView;
    }

    return *this;
};

template <typename T> const T Vector<T>::operator[](const size_t position) const
{
    if (position >= mView.length)
        throw OutOfBoundsException(1, position, 1, mView.length);

    std::shared_lock<std::shared_mutex> mutex(mMut);
    size_t pos = mView.startPos + position;

    return static_cast<MatrixStorage<T>::DataType*>(mData.get())->data[pos];
};

template <typename T> T& Vector<T>::operator[](const size_t position)
{
    if (position >= mView.length)
        throw OutOfBoundsException(1, position, 1, mView.length);
    
    std::unique_lock<std::shared_mutex> lock(mMut);
    size_t pos = (mView.data + mView.startCol * mView.startColStride + mView.startRow * mView.startRowStride) + position;

    return static_cast<MatrixStorage<T>::DataType*>(mData.get())->data[pos];
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

    MatrixKernel<T>::ViewType view {
        .data = mView.data + 
    };
};


        // it's important if the vector is transposed!!
        Vector operator+(const Vector& other) const;
        Vector& operator+=(const Vector& other);
        Matrix<T> operator+=(const Matrix<T>& mat) const;
        Matrix<T>& operator+=(Matrix<T>& mat);

        Vector operator*(const Vector& ohter) const;
        Vector& operator*=(const Vector& ohter);
        Vector operator*(const Matrix<T>& mat) const;
        Vector& operator*(const Matrix<T>& mat);
        
        size_t getLen() const;
        void transpose();

        Vector clone() const;
        Vector subvector(size_t start, size_t len) const;
