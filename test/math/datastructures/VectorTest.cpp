#include "../../testdef.hpp"
#include <cstddef>
#include <mlt/math/Vector.hpp>

using namespace mlt::math::datastructures;

static std::vector<float> getTestVec(size_t len, float start)
{
    std::vector<float> vec;

    for (size_t i = 0; i < len; ++i)
        vec.push_back(start + i);

    return vec;
}

static std::vector<double> getTestVec(size_t len, double start)
{
    std::vector<double> vec;

    for (size_t i = 0; i < len; ++i)
        vec.push_back(start + i);

    return vec;
}

static void testVectorConstructor()
{
    {
        const size_t length = 8;
        Vector<float> vec(length);

        for (size_t i = 0; i < length; i++)
        {
            float val = vec[i];
            assertEq(val, 0.f, "Default Vector construction failed");
        }

        float buffer[8] = {0.f, 1.f, 2.f, 3.f, 4.f, 5.f, 6.f, 7.f};
        Vector<float> buffVec(buffer);

        for (size_t i = 0; i < length; i++)
        {
            float val = buffVec[i];
            assertEq(val, buffer[i], "Vector construction with buffer failed");
        }
    }

    {
        const size_t length = 8;
        Vector<double> vec(length);

        for (size_t i = 0; i < length; i++)
        {
            double val = vec[i];
            assertEq(val, 0., "Default Vector construction failed");
        }

        double buffer[8] = {0., 1., 2., 3., 4., 5., 6., 7.};
        Vector<double> buffVec(buffer);

        for (size_t i = 0; i < length; i++)
        {
            double val = buffVec[i];
            assertEq(val, buffer[i], "Vector construction with buffer failed");
        }
    }
}

static void testVectorGetters()
{
    constexpr size_t size = 10;
    constexpr bool expectedTransposed = false;

    {
        std::vector<float> buffOne = getTestVec(size, 1.f);
        std::vector<float> buffTwo = getTestVec(size, 10.f);
        Vector<float> v1 = Vector<float>(std::span<const float>(buffOne));
        Vector<float> v2 = Vector<float>(std::span<const float>(buffTwo));

        Vector<float> v3 = v1 + v2;

        for (size_t i = 0; i < size; i++)
        {
            const float val = v3[i];
            const float desiredResult = buffOne[i] + buffTwo[i];
            assertEq(val, desiredResult, "flaot Vector addition went wrong.");
        }

        v1 += v3;

        for (size_t i = 0; i < size; i++)
        {
            const float val = v1[i];
            const float desiredResult = buffOne[i] + v3[i];
            assertEq(val, desiredResult, "float Vector in place addition went wrong.");
        }

        assertEq(v1.getLen(), size, "Vector float getter for size produced wrong output.");
        assertEq(v1.isTransposed(), expectedTransposed, "Vector flaot transposed produced wrong output.");
    }

    {
        std::vector<double> buffOne = getTestVec(size, 1.);
        std::vector<double> buffTwo = getTestVec(size, 10.);
        Vector<double> v1 = Vector(std::span<const double>(buffOne));
        Vector<double> v2 = Vector(std::span<const double>(buffTwo));

        Vector<double> v3 = v1 + v2;

        for (size_t i = 0; i < size; i++)
        {
            const double val = v3[i];
            const double desiredResult = buffOne[i] + buffTwo[i];
            assertEq(val, desiredResult, "double Vector addition went wrong.");
        }

        v1 += v3;

        for (size_t i = 0; i < size; i++)
        {
            const double val = v1[i];
            const double desiredResult = buffOne[i] + v3[i];
            assertEq(val, desiredResult, "double Vector in place addition went wrong.");
        }

        assertEq(v1.getLen(), size, "Vector double getter for size produced wrong output.");
        assertEq(v1.isTransposed(), expectedTransposed, "Vector double transposed produced wrong output.");
    }
}

static void testVectorSetter()
{
    constexpr bool expectedTransposed = true;

    {
        size_t size = 10;
        std::vector<float> dataVec = getTestVec(size, 1.f);
        Vector<float> vec(size);

        for (size_t i = 0; i < size; i++)
        {
            vec[i] = dataVec[i];

            float val = vec[i];
            assertEq(val, dataVec[i], "Vector float setter failed");
        }

        vec.transpose();
        assertEq(vec.isTransposed(), expectedTransposed, "Vector flaot transposed() method is broken.");
    }

    {
        size_t size = 10;
        std::vector<double> dataVec = getTestVec(size, 1.);
        Vector<double> vec(size);

        for (size_t i = 0; i < size; i++)
        {
            vec[i] = dataVec[i];

            double val = vec[i];
            assertEq(val, dataVec[i], "Vector float setter failed");
        }

        vec.transpose();
        assertEq(vec.isTransposed(), expectedTransposed, "Vector double transposed() method is broken.");
    }
}

static void testVectorMultiplicationOperator()
{
    constexpr size_t size = 10;

    {
        constexpr float mulConst = 2.f;

        std::vector<float> buff = getTestVec(size, 1.f);
        Vector<float> v = Vector(std::span<const float>(buff));

        Vector<float> vm = v * mulConst;

        for (size_t i = 0; i < size; i++)
        {
            const float val = vm[i];
            const float desiredResult = buff[i] * mulConst;
            assertEq(val, desiredResult, "double Vector addition went wrong.");
        }
    }

    {
        constexpr double mulConst = 2.;

        std::vector<double> buff = getTestVec(size, 1.);
        Vector<double> v = Vector(std::span<const double>(buff));

        Vector<double> vm = v * mulConst;

        for (size_t i = 0; i < size; i++)
        {
            const double val = vm[i];
            const double desiredResult = buff[i] * mulConst;
            assertEq(val, desiredResult, "double Vector addition went wrong.");
        }
    }
}

static void testVectorMultiplicationEqualOperator()
{
    constexpr size_t size = 10;

    {
        constexpr float mulConst = 2.f;

        std::vector<float> buff = getTestVec(size, 1.f);
        Vector<float> v = Vector(std::span<const float>(buff));

        v *= mulConst;

        for (size_t i = 0; i < size; i++)
        {
            const float val = v[i];
            const float desiredResult = buff[i] * mulConst;
            assertEq(val, desiredResult, "double Vector addition went wrong.");
        }
    }

    {
        constexpr double mulConst = 2.;

        std::vector<double> buff = getTestVec(size, 1.);
        Vector<double> v = Vector(std::span<const double>(buff));

        v *= mulConst;

        for (size_t i = 0; i < size; i++)
        {
            const double val = v[i];
            const double desiredResult = buff[i] * mulConst;
            assertEq(val, desiredResult, "double Vector addition went wrong.");
        }
    }
}

static void testVectorSubtractionOperator()
{
    constexpr size_t size = 10;

    {
        std::vector<float> buffV1 = getTestVec(size, 1.f);
        std::vector<float> buffV2 = getTestVec(size, 5.f);

        Vector<float> v1 = Vector(std::span<const float>(buffV1));
        Vector<float> v2 = Vector(std::span<const float>(buffV2));

        Vector<float> vm = v1 - v2;

        for (size_t i = 0; i < size; i++)
        {
            const float val = vm[i];
            const float desiredResult = buffV1[i] - buffV2[i];
            assertEq(val, desiredResult, "float Vector subtraction went wrong.");
        }
    }

    {
        std::vector<double> buffV1 = getTestVec(size, 1.);
        std::vector<double> buffV2 = getTestVec(size, 5.);

        Vector<double> v1 = Vector(std::span<const double>(buffV1));
        Vector<double> v2 = Vector(std::span<const double>(buffV2));

        Vector<double> vm = v1 - v2;

        for (size_t i = 0; i < size; i++)
        {
            const double val = vm[i];
            const double desiredResult = buffV1[i] - buffV2[i];
            assertEq(val, desiredResult, "double Vector subtraction went wrong.");
        }
    }
}

static void testVectorSubtractionEqualsOperator()
{
    constexpr size_t size = 10;

    {
        std::vector<float> buffV1 = getTestVec(size, 1.f);
        std::vector<float> buffV2 = getTestVec(size, 5.f);

        Vector<float> v1 = Vector(std::span<const float>(buffV1));
        Vector<float> v2 = Vector(std::span<const float>(buffV2));

        v1 -= v2;

        for (size_t i = 0; i < size; i++)
        {
            const float val = v1[i];
            const float desiredResult = buffV1[i] - buffV2[i];
            assertEq(val, desiredResult, "float Vector subtraction went wrong.");
        }
    }

    {
        std::vector<double> buffV1 = getTestVec(size, 1.);
        std::vector<double> buffV2 = getTestVec(size, 5.);

        Vector<double> v1 = Vector(std::span<const double>(buffV1));
        Vector<double> v2 = Vector(std::span<const double>(buffV2));

        v1 -= v2;

        for (size_t i = 0; i < size; i++)
        {
            const double val = v1[i];
            const double desiredResult = buffV1[i] - buffV2[i];
            assertEq(val, desiredResult, "double Vector subtraction went wrong.");
        }
    }
}

REGISTER_TEST(testVectorConstructor);
REGISTER_TEST(testVectorSetter);
REGISTER_TEST(testVectorGetters);
REGISTER_TEST(testVectorMultiplicationOperator);
REGISTER_TEST(testVectorMultiplicationEqualOperator);
REGISTER_TEST(testVectorSubtractionOperator);
REGISTER_TEST(testVectorSubtractionEqualsOperator);
