#include "../testdef.hpp"

#include <expected>
#include <iterator>
#include <mlt/internal/compute/core/SizeArray.hpp>
#include <mlt/internal/compute/core/MltArray.hpp>

using namespace mlt::compute::core;

static void MltArrayFromTest()
{
    const SizeArray<> shape = {2, 2, 3, 3};
    const SizeArray<> strides = {18, 9, 3, 1};

    MltArray arr = MltArray::from(SizeArray(shape));

    for (size_t i = 0; i < arr.shape.size(); ++i)
         assertEq(arr.shape[i], shape[i], "Shape was not initialized properly.");

    for (size_t i = 0; i < arr.strides.size(); ++i)
        assertEq(arr.strides[i], strides[i], "Strides were not initialized properly.");
}

static void MltArrayAtTest()
{
    const float testValues[] = { 1.f, 2.f, 3.f, 4.f };

    SizeArray<> shape = {2, 2};
    MltArray arr = MltArray::from(std::move(shape));

    for (size_t i = 0; i < shape[0]; i++)
    {
        for (size_t j = 0; j < shape[1]; j++)
        {
            if (std::expected<float*, ComputeError> val = arr.at<float>(i, j))
                *val.value() = testValues[i+j];
        }
    }

    for (size_t i = 0; i < shape[0]; i++)
    {
        for (size_t j = 0; j < shape[1]; j++)
        {
            std::expected<float*, ComputeError> val = arr.at<float>(i, j);
            assertEq(*val.value(), testValues[i+j], "");
        }
    }
}

static void MltArrayRowMajorTransposeTest()
{
    const float testValues[] = { 1.f, 2.f, 3.f, 4.f };

    SizeArray<> shape = {2,2};
    MltArray arr = MltArray::from(std::move(shape));

    for (size_t i = 0; i < shape[0]; i++)
    {
        for (size_t j = 0; j < shape[1]; j++)
        {
            if (std::expected<float*, ComputeError> val = arr.at<float>(i, j))
                *val.value() = testValues[i+j];
        }
    }

    MltArray transposed = arr.transpose();

    // assertEq(transposed.at<float>(0,0), testValues[0], "Transpose failed (0,0).");
    // assertEq(transposed.at<float>(0,1), testValues[2], "Transpose failed (0,1).");
    // assertEq(transposed.at<float>(1,0), testValues[1], "Transpose failed (1,0).");
    // assertEq(transposed.at<float>(1,1), testValues[3], "Transpose failed (1,1).");
}

REGISTER_TEST(MltArrayFromTest)
REGISTER_TEST(MltArrayAtTest)
REGISTER_TEST(MltArrayRowMajorTransposeTest)
