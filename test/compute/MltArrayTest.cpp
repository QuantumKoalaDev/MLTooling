#include "../testdef.hpp"

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

    arr.at<float>(0, 0) = testValues[0];
    arr.at<float>(0, 1) = testValues[1];
    arr.at<float>(1, 0) = testValues[2];
    arr.at<float>(1, 1) = testValues[3];

    assertEq(arr.at<float>(0,0), testValues[0],  "");
    assertEq(arr.at<float>(0,1), testValues[1],  "");
    assertEq(arr.at<float>(1,0), testValues[2],  "");
    assertEq(arr.at<float>(1,1), testValues[3],  "");
}

static void MltArrayRowMajorTransposeTest()
{
    const float testValues[] = { 1.f, 2.f, 3.f, 4.f };

    SizeArray<> shape = {2,2};
    MltArray arr = MltArray::from(std::move(shape));

    arr.at<float>(0, 0) = testValues[0];
    arr.at<float>(0, 1) = testValues[1];
    arr.at<float>(1, 0) = testValues[2];
    arr.at<float>(1, 1) = testValues[3];

    MltArray transposed = arr.transpose();

    assertEq(transposed.at<float>(0,0), testValues[0], "Transpose failed (0,0).");
    assertEq(transposed.at<float>(0,1), testValues[2], "Transpose failed (0,1).");
    assertEq(transposed.at<float>(1,0), testValues[1], "Transpose failed (1,0).");
    assertEq(transposed.at<float>(1,1), testValues[3], "Transpose failed (1,1).");
}

REGISTER_TEST(MltArrayFromTest)
REGISTER_TEST(MltArrayAtTest)
REGISTER_TEST(MltArrayRowMajorTransposeTest)
