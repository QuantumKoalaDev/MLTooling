#pragma once

#include <math/datastructures/matrix.hpp>
#include <math/datastructures/matrixview.hpp>
#include <math/kernels/matrixkernels.hpp>
#include <math/mathstatus.hpp>

namespace mlt::math::kernels
{
    template <typename T> struct MatrixKernel;

    template <> struct MatrixKernel<float>
    {
        using ViewType = datastructures::MatrixFloatView;
        using DataType = datastructures::MatrixFloat;

        [[nodiscard]] static mlt::math::mathStatus
        add(const ViewType& summandOne, const ViewType& summandTwo, ViewType& result)
        {
            return addMatrixFloat(summandOne, summandTwo, result);
        };
        
        [[nodiscard]] static mlt::math::mathStatus
        addInPlace(ViewType& target, const ViewType& addend)
        {
            return addMatrixFloatInPlace(target, addend);
        };
    };

    template <> struct MatrixKernel<double>
    {
        using ViewType = datastructures::MatrixDoubleView;
        using DataType = datastructures::MatrixDouble;

        [[nodiscard]] static mlt::math::mathStatus
        add(const ViewType& summandOne, const ViewType& summandTwo, ViewType& result)
        {
            return addMatrixDouble(summandOne, summandTwo, result);
        };
        
        [[nodiscard]] static mlt::math::mathStatus
        addInPlace(ViewType& target, const ViewType& addend)
        {
            return addMatrixDoubleInPlace(target, addend);
        };
    };
} // namespace mlt::math::kernels
