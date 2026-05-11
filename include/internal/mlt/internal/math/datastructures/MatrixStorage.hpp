#pragma once

#include <mlt/internal/math/datastructures/matrix.hpp>
#include <mlt/internal/math/mathstatus.hpp>

namespace mlt::math
{
    template <typename T> struct MatrixStorage;

    template <> struct MatrixStorage<float>
    {
        using DataType = mlt::math::MatrixFloat;

        static mlt::math::mathStatus create(const size_t rowCount, const size_t colCount, DataType& out)
        {
            return createMatrixFloat(rowCount, colCount, out);
        }

        static mlt::math::mathStatus createFromBuff(
            const size_t rowCount, const size_t colCount, const float* const buff, const size_t buffLength,
            DataType& out
        )
        {
            return createMatrixFloatFromBuff(rowCount, colCount, buff, buffLength, out);
        }

        static void del(DataType& mat) { deleteMatrixFloat(mat); }
    };

    template <> struct MatrixStorage<double>
    {
        using DataType = mlt::math::MatrixDouble;

        static mlt::math::mathStatus create(const size_t rowCount, const size_t colCount, DataType& out)
        {
            return createMatrixDouble(rowCount, colCount, out);
        }

        static mlt::math::mathStatus createFromBuff(
            const size_t rowCount, const size_t colCount, const double* const buff, const size_t buffLength,
            DataType& out
        )
        {
            return createMatrixDoubleFromBuff(rowCount, colCount, buff, buffLength, out);
        }

        static void del(DataType& mat) { deleteMatrixDouble(mat); }
    };

} // namespace mlt::math
