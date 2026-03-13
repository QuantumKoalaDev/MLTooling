#pragma once

#include <math/datastructures/matrixview.hpp>
#include <math/mathstatus.hpp>

#include <cstddef>

namespace mlt::math::datastructures
{

    struct MatrixFloat
    {
        float* data;
        size_t rows;
        size_t cols;
        size_t stride;
    };

    [[nodiscard]] mlt::math::mathStatus createMatrixFloat(size_t r, size_t c, MatrixFloat& out);
    [[nodiscard]] mlt::math::mathStatus
    createMatrixFloatFromBuff(size_t r, size_t c, const float* buf, size_t bufLength, MatrixFloat& out);
    void deleteMatrixFloat(MatrixFloat& mat);

    [[nodiscard]] mlt::math::mathStatus addRowFloat(const float* row, size_t rowLength, size_t atRow, MatrixFloat& mat);
    [[nodiscard]] mlt::math::mathStatus addColFloat(const float* col, size_t colLength, size_t atCol, MatrixFloat& mat);
    [[nodiscard]] mlt::math::mathStatus resizeMatrixFloat(MatrixFloat& mat, size_t cSize, size_t rSize);
    [[nodiscard]] MatrixFloatView getMatrixFloatView(const MatrixFloat& mat);

    struct MatrixDouble
    {
        double* data;
        size_t rows;
        size_t cols;
        size_t stride;
    };

    [[nodiscard]] mlt::math::mathStatus createMatrixDouble(size_t r, size_t c, MatrixDouble& out);
    [[nodiscard]] mlt::math::mathStatus
    createMatrixDoubleFromBuff(size_t r, size_t c, const double* buff, size_t buffLength, MatrixDouble& out);
    void deleteMatrixDouble(MatrixDouble& mat);

    [[nodiscard]] mlt::math::mathStatus
    addRowDouble(const double* row, size_t rowLength, size_t atRow, MatrixDouble& mat);
    [[nodiscard]] mlt::math::mathStatus
    addColDouble(const double* col, size_t colLength, size_t atCol, MatrixDouble& mat);
    [[nodiscard]] mlt::math::mathStatus resizeMatrixDouble(MatrixDouble& mat, size_t cSize, size_t rSize);
    [[nodiscard]] MatrixDoubleView getMatrixDoubleView(const MatrixDouble& mat);
} // namespace mlt::math::datastructures
