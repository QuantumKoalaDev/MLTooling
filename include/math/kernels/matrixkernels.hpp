#pragma once

#include <math/datastructures/matrixview.hpp>
#include <math/mathstatus.hpp>

namespace mlt::math::kernels
{
    [[nodiscard]] mathStatus addMatrixFloat(
        const datastructures::MatrixFloatView& summandOne, const datastructures::MatrixFloatView& summandTwo,
        datastructures::MatrixFloatView& result
    );

    [[nodiscard]] mathStatus addMatrixDouble(
        const datastructures::MatrixDoubleView& summandOne, const datastructures::MatrixDoubleView& summandTwo,
        datastructures::MatrixDoubleView& result
    );

    [[nodiscard]] mathStatus
    addMatrixFloatInPlace(datastructures::MatrixFloatView& target, const datastructures::MatrixFloatView& addend);

    [[nodiscard]] mathStatus
    addMatrixDoubleInPlace(datastructures::MatrixDoubleView& target, const datastructures::MatrixDoubleView& addend);

    // kernels
    // mlt::math::mathStatus getRowFloat(MatrixFloatView& matView, size_t row, float* out);
    // mlt::math::mathStatus getColFloat(MatrixFloatView& matView, size_t col, float* out);
    // mlt::math::mathStatus getElement(MatrixFloatView& matView, size_t row, size_t col, float& out);
    // mlt::math::mathStatus setElement(MatrixFloatView& matView, size_t row, size_t col, float value);
    // mlt::math::mathStatus transpose(const MatrixFloatView& src, MatrixFloatView& dist);
    // mlt::math::mathStatus fill(MatrixFloatView& mat, float value);
    // mlt::math::mathStatus setZero(MatrixFloatView& mat);
    // mlt::math::mathStatus setIdentity(MatrixFloatView& mat);
    // mlt::math::mathStatus copy(const MatrixFloatView& src, MatrixFloatView& dist);

    // mlt::math::mathStatus submatrix(
    //  const MatrixFloatView& src, size_t rowStart, size_t rowEnd, size_t colStart, size_t colEnd, MatrixFloatView& out
    // );
} // namespace mlt::math::kernels
