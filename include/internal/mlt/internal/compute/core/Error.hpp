#pragma once

#include <format>
#include <string>
#include <string_view>

namespace mlt::compute::core
{
    enum class ComputeErrorType
    {
        TypeMismatch,
        ShapeMismatch,
        RankMismatch,
        OutOfBounds,
        NotImplemented
    };

    struct ComputeError
    {
        ComputeErrorType type;
        std::string msg;
    };

    inline std::string getTypeMismatchMsg(std::string_view expected, std::string_view got)
    {
        return std::format("Expected type: {}, Got: {}", expected, got);
    }

    inline std::string getRankMismatchMsg(const size_t expected, const size_t got)
    {
        return std::format("Expected rank: {}, Got: {}", expected, got);
    }

    inline std::string getOutOfBoundsMsg(const size_t allowed, const size_t got)
    {
        return std::format("Allowed max: {}, Got: {}", allowed, got);
    }

    inline std::string getNotImplementedMsg()
    {
        return "Functionality currently not implemented.";
    }
}
