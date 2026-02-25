#include "../../testdef.hpp"
#include <math/datastructures/Matrix.hpp>

using namespace mlt::math::datastructures;

std::vector<float> getTestVec(size_t len, int start)
{
    std::vector<float> vec;

    for (size_t i = 0; i < len; ++i)
        vec.push_back(start + i);

    return vec;
}


static void testConstructorMatrix()
{
    // Test for 1x1
    {
        Matrix<float> mat(1,1);
        const float val = mat[0,0];

        assertEq(val, 0.f, "Default Matrix construction failed.");

        std::vector<float> vec = { 5.f };
        Matrix<float> matBuff(1,1, vec);
        const float valBuff = matBuff[0,0];

        assertEq(valBuff, vec[0], "Default matrix construction with buffer failed.");
    }

    // Test for 5x7
    {
        Matrix<float> mat(5,7);
        const float val = mat[1,2];
        assertEq(val, 0.f, "Default Matrix construction failed.");

        std::vector<float> buff = getTestVec(35, 4); 
        Matrix<float> matBuff(5,7, buff);

        const float testValOne = matBuff[0, 0];
        assertEq(testValOne, buff[0], "Col major layout broke.");
        assertEq(matBuff[4,6], buff[34], "Col major layout broke.");
        assertEq(matBuff[3, 6], buff[33], "Col major layout broke.");
        assertEq(matBuff[1, 0], buff[1], "Col major layout broke.");
    }
}

static void testGetSetOperator()
{
    // Test for 5x7
    {
        std::vector<float> buff = getTestVec(35, 5);
        Matrix<float> mat(5, 7, buff);

        mat[2, 4] = 24.f;
        assertEq(mat[2,4], 24.f, "Value was not set.");
    }
}

REGISTER_TEST(testConstructorMatrix);
REGISTER_TEST(testGetSetOperator);
