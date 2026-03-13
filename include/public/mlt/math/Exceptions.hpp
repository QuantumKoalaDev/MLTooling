#pragma once

#include <exception>
#include <stdexcept>
#include <string>

namespace mlt::math
{
    class AllocationException : public std::exception
    {
      protected:
        std::string mMsg;

      public:
        explicit AllocationException(const std::string& message) : mMsg(message) {}
        const char* what() const noexcept override { return mMsg.c_str(); }
    };

    class AllocationFailedException : public AllocationException
    {
      public:
        AllocationFailedException() :
            AllocationException("AllocationFailed. Memory could not be initialized correctly.")
        {
        }
    };

    class AllocationTooLargeException : public AllocationException
    {
      public:
        AllocationTooLargeException(const size_t typeSize, const size_t rows, const size_t cols = 1) :
            AllocationException(
                "Requested block too large: " + std::to_string(rows) + "x" + std::to_string(cols) +
                " Bytes: " + std::to_string(rows * cols * typeSize)
            )
        {
        }
    };

    class OutOfBoundsException : public std::out_of_range
    {
      public:
        OutOfBoundsException(const size_t row, const size_t col, size_t maxRow, const size_t maxCol) :
            std::out_of_range(
                "Index out of bounds: requested (" + std::to_string(row) + "," + std::to_string(col) + "), max is (" +
                std::to_string(maxRow - 1) + "," + std::to_string(maxCol - 1) + ")"
            )
        {
        }
    };

    class ShapeMismatchException : public std::logic_error
    {
      public:
        ShapeMismatchException(const size_t lhsRows, const size_t lhsCols, const size_t rhsRows, const size_t rhsCols) :
            std::logic_error(
                "Shape mismatch: lhs (" + std::to_string(lhsRows) + "x" + std::to_string(lhsCols) + "), rhs (" +
                std::to_string(rhsRows) + "x" + std::to_string(rhsCols) + ")"
            )
        {
        }
    };

} // namespace mlt::math
