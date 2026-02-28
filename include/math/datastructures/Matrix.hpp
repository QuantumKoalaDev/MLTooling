#pragma once

#include <memory>
#include <shared_mutex>
#include <vector>

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
        Matrix(size_t rowCount, size_t colCount, std::vector<T> buff);

        ~Matrix();

        Matrix(Matrix&& other) noexcept : mData(std::move(other.mData)), mView(other.mView) {}

        const T operator[](size_t row, size_t col) const;
        T& operator[](size_t row, size_t col);

        Matrix operator+(const Matrix& other) const;
        Matrix& operator+=(const Matrix& other);

        Matrix operator*(const Matrix& other) const;
    };

    extern template class Matrix<float>;
    extern template class Matrix<double>;

} // namespace mlt::math::datastructures
