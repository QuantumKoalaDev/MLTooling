#pragma once

#include <mlt/core/Shape.hpp>
#include <mlt/math/Matrix.hpp>

#include <mutex>
#include <ranges>
#include <shared_mutex>
#include <span>
#include <memory>

namespace mlt::math::datastructures {
    template <typename T> class Vector
    {
        struct VectorView
        {
            size_t startPos;
            size_t length;
            size_t stride;
            bool transposed;
        };

        VectorView mView;
        std::shared_ptr<void> mData;
        mutable std::shared_mutex mMut;

    public:
        class ElementProxy
        {
            Vector* mParent;
            size_t mIndex;
            std::unique_lock<std::shared_mutex> mLock;

        public:
            ElementProxy(Vector* v, size_t i, std::unique_lock<std::shared_mutex> lock) : mParent(v), mIndex(i), mLock(lock) {};
            
        };


        explicit Vector(size_t len);
        Vector(size_t len, std::span<const T> buff);
        
        ~Vector();
        
        Vector(const Vector& other) noexcept : mData(other.mData), mView(other.mView) {}
        Vector(Vector&& other) noexcept: mData(std::move(other.mData)), mView(other.mView) {}

        Vector& operator=(const Vector& other) noexcept;
        Vector& operator=(Vector&& ohter) noexcept;

        const T operator[](size_t position) const;
        T& operator[](size_t position);


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
    };

    extern template class Vector<float>;
    extern template class Vector<double>;
}


template<typename T>
class Vector {
private:
    struct VectorView {
        size_t startCol;
        size_t startRow;
        size_t length;
        size_t stride;
        bool transposed;
    };

    VectorView mView;
    std::shared_ptr<void> mData;
    mutable std::shared_mutex mMut;

    using Storage = MatrixStorage<T>::DataType;

public:
    // Proxy für sicheren Zugriff
    class ElementProxy {
        Vector* parent;
        size_t index;
        std::unique_lock<std::shared_mutex> lock;

    public:
        ElementProxy(Vector* v, size_t i)
            : parent(v), index(i), lock(v->mMut) {}

        // Assignment
        ElementProxy& operator=(const T& value) {
            static_cast<Storage*>(parent->mData.get())->data[index] = value;
            return *this;
        }

        // Conversion operator für Lesezugriff
        operator T() const {
            return static_cast<Storage*>(parent->mData.get())->data[index];
        }

        // Optional: Zugriff als Referenz für kompliziertere Operationen
        T& get_ref() {
            return static_cast<Storage*>(parent->mData.get())->data[index];
        }
    };

    // Operator[] gibt Proxy zurück
    ElementProxy operator[](size_t position) {
        if (position >= mView.length)
            throw OutOfBoundsException(1, position, 1, mView.length);

        size_t pos = (mView.startCol * mView.stride + mView.startRow) + position;
        return ElementProxy(this, pos);
    }

    // Const Version für lesenden Zugriff
    T operator[](size_t position) const {
        if (position >= mView.length)
            throw OutOfBoundsException(1, position, 1, mView.length);

        std::shared_lock lock(mMut);
        size_t pos = (mView.startCol * mView.stride + mView.startRow) + position;
        return static_cast<Storage*>(mData.get())->data[pos];
    }
};
