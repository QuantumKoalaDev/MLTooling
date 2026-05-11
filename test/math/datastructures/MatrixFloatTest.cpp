#include "../../testdef.hpp"
#include <mlt/internal/math/datastructures/matrix.hpp>
#include <mlt/internal/math/mathstatus.hpp>

#include <vector>

#define CHECK_CREATE_STATUS checkSuccessfullStatus(createStat, "Matrix allocation failed.");

using namespace mlt::math;
using FloatVec = std::vector<float>;

inline void checkSuccessfullStatus(mlt::math::mathStatus stat, std::string msg)
{
    assertEq(stat, mlt::math::MATH_SUCCESS, msg);
}

FloatVec getTestVec(int start, int end)
{
    FloatVec vec;

    for (int i = start; i < end; ++i)
        vec.push_back(i);

    return vec;
}

FloatVec fillVec(float val, size_t length)
{
    FloatVec vec;

    for (size_t i = 0; i < length; ++i)
        vec.push_back(val);

    return vec;
}

static void testConstruction()
{
    // Test for 1x1
    {
        MatrixFloat mat;
        mlt::math::mathStatus createStat = createMatrixFloat(1, 1, mat);
        CHECK_CREATE_STATUS
        assertEq(mat.rows, static_cast<size_t>(1), "Rows incorrect.");
        assertEq(mat.cols, static_cast<size_t>(1), "Cols incorrect.");
        assertEq(mat.data[0], 0.f, "1x1 matrix not zero initialized.");

        deleteMatrixFloat(mat);
    }

    // Test for 2x5
    {
        MatrixFloat mat;
        mlt::math::mathStatus createStat = createMatrixFloat(2, 5, mat);
        CHECK_CREATE_STATUS

        assertEq(mat.rows, static_cast<size_t>(2), "Rows incorrect.");
        assertEq(mat.cols, static_cast<size_t>(5), "Cols incorrect.");

        for (size_t i = 0; i < 10; ++i)
            assertEq(mat.data[i], 0.f, "Matrix not zero initialized.");

        deleteMatrixFloat(mat);
    }

    // Test for 3x4
    {
        FloatVec buff = getTestVec(0, 12);
        MatrixFloat mat;
        mlt::math::mathStatus createStat = createMatrixFloatFromBuff(3, 4, buff.data(), buff.size(), mat);
        CHECK_CREATE_STATUS

        for (size_t col = 0; col < 4; ++col)
        {
            for (size_t row = 0; row < 3; ++row)
            {
                size_t index = col * 3 + row;
                assertEq(mat.data[index], buff[index], "Column-major layout broken.");
            }
        }

        deleteMatrixFloat(mat);
    }

    // Test for wrong buffersize
    {
        FloatVec buff = getTestVec(0, 5);
        MatrixFloat mat;
        mlt::math::mathStatus createStat = createMatrixFloatFromBuff(3, 3, buff.data(), buff.size(), mat);

        if (createStat == mlt::math::MATH_SUCCESS)
            deleteMatrixFloat(mat);

        assertTrue(createStat != mlt::math::MATH_SUCCESS, "Matrix creation should fail for wrong buffer size.");
    }
}

static void testAddRow()
{
    FloatVec testVec = getTestVec(-4.f, 96.f);
    MatrixFloat mat;
    mlt::math::mathStatus createStat = createMatrixFloatFromBuff(10, 10, testVec.data(), testVec.size(), mat);

    FloatVec testRow = getTestVec(-20.f, -10.f);
    mlt::math::mathStatus addRowStat = addRowFloat(testRow.data(), testRow.size(), 10, mat);

    CHECK_CREATE_STATUS

    FloatVec expected;

    for (size_t c = 0; c < 10; ++c)
    {
        std::span<float> colSpan(testVec.data() + c * 10, 10);
        expected.append_range(colSpan);

        expected.push_back(testRow[c]);
    }

    assertEq(FloatVec(mat.data, mat.data + mat.rows * mat.cols), expected, "Failed add row to matrix.");

    deleteMatrixFloat(mat);
}

static void testAddCol()
{
    FloatVec testVec = getTestVec(2.f, 26.f);
    MatrixFloat mat;
    mlt::math::mathStatus createStat = createMatrixFloatFromBuff(6, 4, testVec.data(), testVec.size(), mat);
    CHECK_CREATE_STATUS

    FloatVec expectedOne = FloatVec(testVec);
    FloatVec rowOne = getTestVec(100.f, 106.f);
    expectedOne.append_range(rowOne);

    mlt::math::mathStatus addOneStat = addColFloat(rowOne.data(), 6, mat.cols, mat);

    checkSuccessfullStatus(addOneStat, "Adding col to matrix failed due to some error. Col was not added.");
    assertEq(FloatVec(mat.data, mat.data + mat.rows * mat.cols), expectedOne, "Failed to add col to matrix.");

    deleteMatrixFloat(mat);
}

REGISTER_TEST(testConstruction);
REGISTER_TEST(testAddRow);
REGISTER_TEST(testAddCol);
