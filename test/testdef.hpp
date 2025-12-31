#pragma once

#include "Testrunner.hpp"

#include <cmath>
#include <format>
#include <iostream>
#include <stdexcept>
#include <string>
#include <typeindex>

#define REGISTER_TEST(func)                                                                                            \
    struct func##_registrar                                                                                            \
    {                                                                                                                  \
        func##_registrar()                                                                                             \
        {                                                                                                              \
            TestRunner::instance().registerTest(#func, func);                                                          \
        }                                                                                                              \
    } func##_instance;

struct AssertionFailed : std::runtime_error
{
    using std::runtime_error::runtime_error;
};

static std::string toString(const std::vector<float>& v)
{
    std::string s = "[";
    for (size_t i = 0; i < v.size(); ++i)
    {
        if (i) s += ", ";
        s += std::to_string(v[i]);
    }
    s += "]";
    return s;
}

template <typename T> void assertEq(const T& actual, const T& expected, const std::string msg)
{
    if (actual != expected)
        throw AssertionFailed(
            msg + std::format(" (expected: {}, got: {})", std::to_string(expected), std::to_string(actual))
        );
}

inline void assertEq(float actual, float expected, std::string msg, float epsilon = 1e-5f)
{
    if (std::fabs(actual - expected) > epsilon)
        throw AssertionFailed(msg + std::format(" (expected: {}, got: {})", expected, actual));
}

inline void assertEq(double actual, double expected, std::string msg, double epsilon = 1e-9)
{
    if (std::fabs(actual - expected) > epsilon)
        throw AssertionFailed(msg + std::format(" (expected: {}, got: {})", expected, actual));
}

inline void
assertEq(const std::vector<float>& actual, const std::vector<float> expected, std::string msg, float epsilon = 1e-6f)
{
    if (actual.size() != expected.size())
        throw AssertionFailed(msg + std::format(" (expected: {}, got: {})", toString(expected), toString(actual)));

    for (size_t i{}; i < actual.size(); ++i) { assertEq(actual[i], expected[i], msg, epsilon); }
}

inline void assertEq(std::string actual, std::string expected, std::string msg)
{
    if (actual != expected) throw AssertionFailed(msg + std::format(" (expected: {}, got: {})", expected, actual));
}

inline void assertEq(std::type_index actual, std::type_index expected, std::string msg)
{
    if (actual != expected)
        throw AssertionFailed(msg + std::format(" (expected: {}, got: {})", expected.name(), actual.name()));
}