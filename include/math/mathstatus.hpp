#pragma once

namespace mlt::math
{
    enum mathStatus
    {
        MATH_SUCCESS,
        MATH_ALLOCATION_FAILED,
        MATH_REQUESTED_ALLOCATION_TO_BIG,
        MATH_MATRIX_OUT_OF_BOUND,
        MATH_SHAPE_MISSMATCH
    };
} // namespace mlt::math
