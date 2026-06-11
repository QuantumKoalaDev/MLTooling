#pragma once

#include <string>

namespace mlt::compute::core
{
    enum class ComputeErrorType
    {
        TypeMismatch,
        ShapeMismatch,
        RankMismatch,
        NotImplemented
    };

    struct ComputeError
    {
        ComputeErrorType type;
        std::string msg;
    };
}
