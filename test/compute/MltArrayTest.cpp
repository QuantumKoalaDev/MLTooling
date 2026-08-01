#include "../testdef.hpp"

#include <expected>
#include <iterator>

#include <mlt/internal/compute/core/MltArray.hpp>

import mlt.internal.compute.core.sizearray;

using namespace mlt::compute::core;

static void MltArrayFromTest()
{
    const SizeArray shape = {2, 2, 3, 3};
    const SizeArray strides = {18, 9, 3, 1};

    MltArray arr = MltArray::from(SizeArray(shape));

    for (size_t i = 0; i < arr.shape.size(); ++i)
         assertEq(arr.shape[i], shape[i], "Shape was not initialized properly.");

    for (size_t i = 0; i < arr.strides.size(); ++i)
        assertEq(arr.strides[i], strides[i], "Strides were not initialized properly.");
}

static void MltArrayAtTest()
{
    const float testValues[] = { 1.f, 2.f, 3.f, 4.f };

    SizeArray shape = {2, 2};
    SizeArray movShape = shape;
    MltArray arr = MltArray::from(std::move(movShape));


    for (size_t i = 0; i < shape[0]; i++)
    {
        for (size_t j = 0; j < shape[1]; j++)
        {
            if (std::expected<float*, ComputeError> val = arr.at(i, j))
                *val.value() = testValues[i+j];
        }
    }


    for (size_t i = 0; i < shape[0]; i++)
    {
        for (size_t j = 0; j < shape[1]; j++)
        {
            std::expected<float*, ComputeError> val = arr.at(i, j);
            assertEq(*val.value(), testValues[i+j], "Value does not match.");
        }
    }
}

static void MltArrayRowMajorTransposeTest()
{
    const float testValues[] = { 1.f, 2.f, 3.f, 4.f };
    SizeArray shape = {2, 2};
    MltArray arr = MltArray::from(std::move(SizeArray(shape)));

    for (size_t i = 0; i < shape[0]; i++)
    {
        for (size_t j = 0; j < shape[1]; j++)
        {
            size_t linIdx = i * shape[1] + j;
            if (std::expected<float*, ComputeError> val = arr.at(i, j))
                **val = testValues[linIdx];
            else
                throwCustomMessage("at() failed while filling test array.");
        }
    }

    MltArray transposed = arr.transpose();

    for (size_t i = 0; i < shape[0]; i++)
    {
        for (size_t j = 0; j < shape[1]; j++)
        {
            // transposed(j, i) == arr(i, j)
            std::expected<float*, ComputeError> original = arr.at(i, j);
            std::expected<float*, ComputeError> transposedVal = transposed.at(j, i);

            if (!original)
                throwCustomMessage("at() failed reading original array.");
            if (!transposedVal)
                throwCustomMessage("at() failed reading transposed array.");

            assertEq(
                *transposedVal.value(),
                *original.value(),
                std::format("Transpose failed at ({},{}).", j, i)
            );
        }
    }
}

static void MltArrayRowMajor3DTransposeTest()
{
    SizeArray shape = {2, 3, 4};
    MltArray arr = MltArray::from(std::move(SizeArray(shape)));

    const size_t d0 = shape[0], d1 = shape[1], d2 = shape[2];
    std::vector<float> testValues(d0 * d1 * d2);
    for (size_t idx = 0; idx < testValues.size(); ++idx)
        testValues[idx] = static_cast<float>(idx);

    for (size_t i = 0; i < d0; i++)
        for (size_t j = 0; j < d1; j++)
            for (size_t k = 0; k < d2; k++)
            {
                size_t linIdx = i * (d1 * d2) + j * d2 + k;
                if (std::expected<float*, ComputeError> val = arr.at(i, j, k))
                    *val.value() = testValues[linIdx];
                else
                    throwCustomMessage("at() failed while filling 3D test array.");
            }

    MltArray transposed = arr.transpose();

    for (size_t i = 0; i < d0; i++)
        for (size_t j = 0; j < d1; j++)
            for (size_t k = 0; k < d2; k++)
            {
                std::expected<float*, ComputeError> original = arr.at(i, j, k);
                //  transposed(k, j, i) == arr(i, j, k)
                std::expected<float*, ComputeError> transposedVal = transposed.at(k, j, i);

                if (!original)
                    throwCustomMessage("at() failed reading original 3D array.");
                if (!transposedVal)
                    throwCustomMessage("at() failed reading transposed 3D array.");

                assertEq(
                    *transposedVal.value(),
                    *original.value(),
                    std::format("3D transpose failed at ({},{},{}).", k, j, i)
                );
            }
}



REGISTER_TEST(MltArrayFromTest)
REGISTER_TEST(MltArrayAtTest)
REGISTER_TEST(MltArrayRowMajorTransposeTest)
REGISTER_TEST(MltArrayRowMajor3DTransposeTest)
