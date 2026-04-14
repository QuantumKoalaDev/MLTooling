#pragma once

#include <mlt/internal/math/datastructures/matrixview.hpp>
#include <mlt/internal/math/mathstatus.hpp>

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

    [[nodiscard]] mathStatus subtractMatrixFloat(
        const datastructures::MatrixFloatView& minuend, const datastructures::MatrixFloatView& subtrahend,
        datastructures::MatrixFloatView& difference
    );

    [[nodiscard]] mathStatus subtractMatrixDouble(
        const datastructures::MatrixDoubleView& minuend, const datastructures::MatrixDoubleView& subtrahend,
        datastructures::MatrixDoubleView& difference
    );

    [[nodiscard]] mathStatus subtractInPlaceMatrixFloat(
        datastructures::MatrixFloatView& difference, const datastructures::MatrixFloatView& subtrahend
    );

    [[nodiscard]] mathStatus subtractInPlaceMatrixDouble(
        datastructures::MatrixDoubleView& difference, const datastructures::MatrixDoubleView& subtrahend
    );

    [[nodiscard]] mathStatus multiplyMatrixFloat(
        const datastructures::MatrixFloatView& multiplicant, const datastructures::MatrixFloatView& multiplier,
        datastructures::MatrixFloatView& product
    );

    [[nodiscard]] mathStatus multiplyMatrixDouble(
        const datastructures::MatrixDoubleView& multiplicant, const datastructures::MatrixDoubleView& multiplier,
        datastructures::MatrixDoubleView& product
    );

    [[nodiscard]] mathStatus multiplyScalarMatrixFloat(
        const datastructures::MatrixFloatView& mat, float scalar, datastructures::MatrixFloatView& result
    );

    [[nodiscard]] mathStatus multiplyScalarMatrixDouble(
        const datastructures::MatrixDoubleView& mat, double scalar, datastructures::MatrixDoubleView& result
    );

    [[nodiscard]] mathStatus multiplyScalarMatrixFloatInPlace(datastructures::MatrixFloatView& mat, float scalar);

    [[nodiscard]] mathStatus multiplyScalarMatrixDoubleInPlace(datastructures::MatrixDoubleView& mat, double scalar);

    [[nodiscard]] mathStatus
    cloneMatrixFloat(const datastructures::MatrixFloatView& src, datastructures::MatrixFloatView& dist);

    [[nodiscard]] mathStatus
    cloneMatrixDouble(const datastructures::MatrixDoubleView& src, datastructures::MatrixDoubleView& dist);

    // kernels
    // mlt::math::mathStatus getRowFloat(MatrixFloatView& matView, size_t row, float* out);
    // mlt::math::mathStatus getColFloat(MatrixFloatView& matView, size_t col, float* out);
    // mlt::math::mathStatus transpose(const MatrixFloatView& src, MatrixFloatView& dist);
    // mlt::math::mathStatus fill(MatrixFloatView& mat, float value);
    // mlt::math::mathStatus setZero(MatrixFloatView& mat);
    // mlt::math::mathStatus setIdentity(MatrixFloatView& mat);

} // namespace mlt::math::kernels
