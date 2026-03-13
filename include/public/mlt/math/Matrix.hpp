#pragma once

#include <mlt/core/Shape.hpp>

#include <memory>
#include <shared_mutex>
#include <span>

struct MatrixFloat;
struct MatrixDouble;

namespace mlt::math::datastructures
{

    struct MatrixView
    {
        size_t startCol;
        size_t startRow;
        size_t cols;
        size_t rows;
        size_t strideCol;
        size_t strideRow;
    };

    template <typename T> class Matrix
    {
        std::shared_ptr<void> mData;
        MatrixView mView;
        mutable std::shared_mutex mMut;

      public:
        Matrix(size_t rowCount, size_t colCount);
        explicit Matrix(core::Shape shape) : Matrix(shape.rows, shape.cols) {};
        Matrix(size_t rowCount, size_t colCount, std::span<const T> buff);
        Matrix(core::Shape shape, std::span<const T> buff) : Matrix(shape.rows, shape.cols, buff) {};

        ~Matrix();

        Matrix(const Matrix& other) noexcept : mData(other.mData), mView(other.mView) {};
        Matrix(Matrix&& other) noexcept : mData(std::move(other.mData)), mView(other.mView) {}

        Matrix& operator=(const Matrix& other) noexcept;
        Matrix& operator=(Matrix&& other) noexcept;

        const T operator[](size_t row, size_t col) const;
        T& operator[](size_t row, size_t col);

        Matrix operator+(const Matrix& other) const;
        Matrix& operator+=(const Matrix& other);

        Matrix operator*(const Matrix& other) const;

        core::Shape getShape() const;

        Matrix clone() const;
        Matrix submatrix(size_t startRow, size_t startCol, size_t rowCount, size_t colCount) const;
    };

    extern template class Matrix<float>;
    extern template class Matrix<double>;

} // namespace mlt::math::datastructures
