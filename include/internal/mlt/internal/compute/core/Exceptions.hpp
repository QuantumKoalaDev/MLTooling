#pragma once

#include <stdexcept>
#include <string>
#include <string_view>
#include <format>

namespace mlt::compute::core
{
    class NotImplementedException : public std::logic_error
    {
        public:
        NotImplementedException() : std::logic_error("Not implemented yet.")
        {}
    };

    class UnsupportedTypeException : public std::logic_error
    {
        public:
        explicit UnsupportedTypeException(std::string_view type) 
            : std::logic_error("Type is not supported: " + std::string(type))
        {}
    };

    class TypeMissmatchException : public std::logic_error
    {
        public:
        TypeMissmatchException(std::string_view expected, std::string_view got)
            : std::logic_error(std::format("Type missmatch: expected: {}, got: {}", expected, got))
        {}
    };

    class RankMissmatchException : public std::logic_error
    {
        public:
        RankMissmatchException(size_t expected, size_t got)
            : std::logic_error("Rankmissmatch: expected " + std::to_string(expected) + ", got " + std::to_string(got))
        {}
    };

    class OutOfBoundsException : public std::logic_error
    {
        public:
        OutOfBoundsException(size_t max, size_t got)
            : std::logic_error("OutOfBounds: max " + std::to_string(max) + ", got " + std::to_string(got))
        {}
    };
}
