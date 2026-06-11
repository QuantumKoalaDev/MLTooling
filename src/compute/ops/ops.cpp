#include "mlt/internal/compute/core/Error.hpp"
#include "mlt/internal/compute/core/SizeArray.hpp"
#include <expected>
#include <format>

#include <mlt/internal/compute/core/DType.hpp>
#include <mlt/internal/compute/ops/ops.hpp>


using namespace mlt::compute;

std::string createShapeMismatchMsg(const core::SizeArray<>& aShape, const core::SizeArray<>& bShape)
{
    return std::format("Shapes do not match: {} and {}", aShape, bShape);
}

std::string createTypeMismatchMsg(const core::DType aType, const core::DType bType)
{
    return std::format("{} and {} are not compatible", toString(aType), toString(bType));
}

std::expected<core::MltArray, core::ComputeError> ops::matmul(const core::MltArray& a, const core::MltArray& b)
{
    if (a.dType != b.dType)
    {
        const core::ComputeError err = { .type = core::ComputeErrorType::TypeMismatch, .msg = createTypeMismatchMsg(a.dType, b.dType) };
        return std::unexpected(err);
    }

    if (a.shape.size() < 2 || b.shape.size() < 2)
    {
        const core::ComputeError err = { .type = core::ComputeErrorType::ShapeMismatch, .msg = "matmul requires rank >= 2" };
        return std::unexpected(err);
    }
    
    constexpr size_t ROW = 0;
    constexpr size_t COL = 1;
    
    std::span<const size_t> aShape = a.shape.span().last(2);
    std::span<const size_t> bShape = b.shape.span().last(2);
    
    if (aShape[COL] != bShape[ROW] || aShape[ROW] != bShape[COL])
    {
        const core::ComputeError err = { 
            .type = core::ComputeErrorType::ShapeMismatch,
            .msg = createShapeMismatchMsg({aShape[ROW], aShape[COL]}, {bShape[ROW], bShape[COL]}) 
        };

        return std::unexpected(err);
    }

    if (a.dType == core::DType::FLOAT64)
    {
        const core::ComputeError err = { .type = core::ComputeErrorType::NotImplemented, .msg = "matmul not yet implemented for FLOAT64" };
        return std::unexpected(err);
    }

    // returns the result form the runtime
    return core::MltArray::from({2}, a.dType);
}

std::expected<core::MltArray, core::ComputeError> ops::add(const core::MltArray& a, const core::MltArray& b)
{
    if (a.dType != b.dType)
    {
        const core::ComputeError err = { .type = core::ComputeErrorType::TypeMismatch, .msg= createTypeMismatchMsg(a.dType, b.dType) };
        return std::unexpected(err);
    }

    if (a.shape.size() != b.shape.size())
    {
        const core::ComputeError err = { .type = core::ComputeErrorType::ShapeMismatch, .msg = createShapeMismatchMsg(a.shape, b.shape) };
        return std::unexpected(err);
    }
    
    for (size_t i = 0; i < a.shape.size(); ++i)
    {
        if (a.shape[i] != b.shape[i])
        {
            const core::ComputeError err = { .type = core::ComputeErrorType::ShapeMismatch, .msg = createShapeMismatchMsg(a.shape, b.shape) };
            return std::unexpected(err);
        }
    }

    if (a.dType == core::DType::FLOAT64)
    {
        const core::ComputeError err = { .type = core::ComputeErrorType::NotImplemented, .msg = "add not yet implemented for FLOAT64" };
        return std::unexpected(err);
    }
    
    // returns the runtime result
    return core::MltArray::from({2});
}

