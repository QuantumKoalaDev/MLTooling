#pragma once

#include <mlt/math/Matrix.hpp>
#include <span>

struct mltMatrixF
{
    mlt::math::datastructures::Matrix<float> implMat;

    mltMatrixF(size_t rows, size_t cols) : implMat(rows, cols) {}
    mltMatrixF(size_t rows, size_t cols, std::span<const float> buff) : implMat(rows, cols, buff) {}
    mltMatrixF(mlt::math::datastructures::Matrix<float>&& mat) : implMat(mat) {}
};

struct mltMatrixD
{
    mlt::math::datastructures::Matrix<double> implMat;

    mltMatrixD(size_t rows, size_t cols) : implMat(rows, cols) {}
    mltMatrixD(size_t rows, size_t cols, std::span<const double> buff) : implMat(rows, cols, buff) {}
    mltMatrixD(mlt::math::datastructures::Matrix<double>&& mat) : implMat(mat) {}
};
