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

static void testConstructorVector()
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

static void testSetter()
{
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
    }
}

REGISTER_TEST(testConstructorVector);
REGISTER_TEST(testSetter);
