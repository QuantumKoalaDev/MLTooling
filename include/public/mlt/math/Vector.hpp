#pragma once

#include "mlt/core/ProxyElement.hpp"
#include <mlt/core/Shape.hpp>
#include <mlt/math/Matrix.hpp>

#include <memory>
#include <shared_mutex>
#include <span>

namespace mlt::math::datastructures
{

    template <typename T> class Vector
    {
        struct VectorView
        {
            size_t length;
            size_t stride;
            size_t start;
            bool transposed;
        };

        VectorView mView;
        std::shared_ptr<void> mData;
        mutable std::shared_mutex mMut;

        static T getImpl(Vector<T>* vec, const std::array<size_t, 1>& dimArray);
        static void setImpl(Vector<T>* vec, const std::array<size_t, 1>& dimArray, T val);

      public:
        explicit Vector(size_t size);
        explicit Vector(std::span<const T> buff);

        ~Vector();

        Vector(const Vector& other) noexcept : mData(other.mData), mView(other.mView) {}
        Vector(Vector&& other) noexcept : mData(std::move(other.mData)), mView(other.mView) {}

        Vector& operator=(const Vector& other) noexcept;
        Vector& operator=(Vector&& other) noexcept;

        T operator[](size_t position) const;
        ProxyElement<Vector<T>*, T, 1> operator[](size_t position);

        Vector operator+(const Vector& other) const;
        Vector& operator+=(const Vector& other);

        Vector operator*(T scalar) const;
        Vector& operator*=(T scalar);

        size_t getLen() const;
        bool isTransposed() const;
        void transpose();

        Vector clone() const;
        Vector subvector(size_t start, size_t len) const;
    };

    extern template class Vector<float>;
    extern template class Vector<double>;
} // namespace mlt::math::datastructures
