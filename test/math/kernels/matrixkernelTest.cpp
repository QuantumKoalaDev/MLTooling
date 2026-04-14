#include "../../testdef.hpp"
#include <mlt/internal/math/datastructures/matrixview.hpp>
#include <mlt/internal/math/mathstatus.hpp>

#include <mlt/internal/math/datastructures/matrix.hpp>
#include <mlt/internal/math/kernels/matrixkernels.hpp>
#include <vector>

using namespace mlt::math::datastructures;
using namespace mlt::math::kernels;
using FloatVec = std::vector<float>;
using DoubleVec = std::vector<double>;

static void matrixKernelAddTest()
{
    FloatVec sumOne = {1, 2, 3, 4, 5, 6};
    FloatVec sumTwo = {6, 5, 4, 3, 2, 1};

    MatrixFloat matOne;
    MatrixFloat matTwo;
    MatrixFloat matResult;

    mlt::math::mathStatus unusedStat;
    unusedStat = createMatrixFloatFromBuff(2, 3, sumOne.data(), sumOne.size(), matOne);
    unusedStat = createMatrixFloatFromBuff(2, 3, sumTwo.data(), sumTwo.size(), matTwo);
    unusedStat = createMatrixFloat(2, 3, matResult);

    MatrixFloatView oneView = getMatrixFloatView(matOne);
    MatrixFloatView twoView = getMatrixFloatView(matTwo);
    MatrixFloatView resultView = getMatrixFloatView(matResult);
    mlt::math::mathStatus addStat = addMatrixFloat(oneView, twoView, resultView);

    assertEq(addStat, mlt::math::MATH_SUCCESS, "Matrix shape was missmatched.");
    assertEq(resultView.data[0], 7.f, "Matrix addition failed.");

    deleteMatrixFloat(matOne);
    deleteMatrixFloat(matOne);
    deleteMatrixFloat(matResult);
}

static void matrixKernelMultiplyTest()
{
    {
        FloatVec aData = {1, 4, 2, 5, 3, 6};
        FloatVec bData = {7, 8, 9, 10, 11, 12};
        FloatVec cData = {50, 122, 68, 167};

        MatrixFloat A;
        MatrixFloat B;
        MatrixFloat C;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixFloatFromBuff(2, 3, aData.data(), aData.size(), A);
        unusedStat = createMatrixFloatFromBuff(3, 2, bData.data(), bData.size(), B);
        unusedStat = createMatrixFloat(2, 2, C);

        MatrixFloatView aView = getMatrixFloatView(A);
        MatrixFloatView bView = getMatrixFloatView(B);
        MatrixFloatView cView = getMatrixFloatView(C);

        mlt::math::mathStatus mulStat = multiplyMatrixFloat(aView, bView, cView);

        assertEq(mulStat, mlt::math::MATH_SUCCESS, "Matrix shape was missmatched (float part).");

        for (size_t i = 0; i < cData.size(); ++i)
            assertEq(cView.data[i], cData[i], "Wrong value (float part).");

        deleteMatrixFloat(A);
        deleteMatrixFloat(B);
        deleteMatrixFloat(C);
    }

    {
        DoubleVec aData = {1, 4, 2, 5, 3, 6};
        DoubleVec bData = {7, 8, 9, 10, 11, 12};
        DoubleVec cData = {50, 122, 68, 167};

        MatrixDouble A;
        MatrixDouble B;
        MatrixDouble C;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixDoubleFromBuff(2, 3, aData.data(), aData.size(), A);
        unusedStat = createMatrixDoubleFromBuff(3, 2, bData.data(), bData.size(), B);
        unusedStat = createMatrixDouble(2, 2, C);

        MatrixDoubleView aView = getMatrixDoubleView(A);
        MatrixDoubleView bView = getMatrixDoubleView(B);
        MatrixDoubleView cView = getMatrixDoubleView(C);

        mlt::math::mathStatus mulStat = multiplyMatrixDouble(aView, bView, cView);

        assertEq(mulStat, mlt::math::MATH_SUCCESS, "Matrix shape was missmatched (dobule part).");

        for (size_t i = 0; i < cData.size(); ++i)
            assertEq(cView.data[i], cData[i], "Wrong value (double part).");

        deleteMatrixDouble(A);
        deleteMatrixDouble(B);
        deleteMatrixDouble(C);
    }
}

static void matrixKernelCloneTest()
{
    {
        FloatVec aData = {1, 4, 2, 5, 3, 6};

        MatrixFloat A;
        MatrixFloat B;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixFloatFromBuff(2, 3, aData.data(), aData.size(), A);
        unusedStat = createMatrixFloat(2, 3, B);

        MatrixFloatView aView = getMatrixFloatView(A);
        MatrixFloatView bView = getMatrixFloatView(B);

        mlt::math::mathStatus cloneStat = cloneMatrixFloat(aView, bView);

        assertEq(cloneStat, mlt::math::MATH_SUCCESS, "Matrix could not be cloned due to shape missmatch (float part).");

        for (size_t i = 0; i < aData.size(); ++i)
            assertEq(bView.data[i], aData[i], "Wrong value (float part).");

        deleteMatrixFloat(A);
        deleteMatrixFloat(B);
    }

    {
        DoubleVec aData = {1, 4, 2, 5, 3, 6};

        MatrixDouble A;
        MatrixDouble B;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixDoubleFromBuff(2, 3, aData.data(), aData.size(), A);
        unusedStat = createMatrixDouble(2, 3, B);

        MatrixDoubleView aView = getMatrixDoubleView(A);
        MatrixDoubleView bView = getMatrixDoubleView(B);

        mlt::math::mathStatus cloneStat = cloneMatrixDouble(aView, bView);

        assertEq(
            cloneStat,
            mlt::math::MATH_SUCCESS,
            "Matrix could not be cloned due to shape missmatch (double part)."
        );

        for (size_t i = 0; i < aData.size(); ++i)
            assertEq(bView.data[i], aData[i], "Wrong value (double part).");

        deleteMatrixDouble(A);
        deleteMatrixDouble(B);
    }
}

static void matrixKernelAddScalarTest()
{
    {
        constexpr float mulConst = 2.f;
        FloatVec aData = {1, 4, 2, 5, 3, 6};

        MatrixFloat A;
        MatrixFloat B;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixFloatFromBuff(2, 3, aData.data(), aData.size(), A);
        unusedStat = createMatrixFloat(2, 3, B);

        MatrixFloatView aView = getMatrixFloatView(A);
        MatrixFloatView bView = getMatrixFloatView(B);
        mlt::math::mathStatus mulStat = multiplyScalarMatrixFloat(aView, mulConst, bView);

        assertEq(mulStat, mlt::math::MATH_SUCCESS, "Matrix scalar multiplication failed (float part).");

        for (size_t i = 0; i < aData.size(); ++i)
            assertEq(bView.data[i], aData[i] * mulConst, "Wrong value (float part).");

        deleteMatrixFloat(A);
        deleteMatrixFloat(B);
    }

    {
        constexpr double mulConst = 2.;
        DoubleVec aData = {1, 4, 2, 5, 3, 6};

        MatrixDouble A;
        MatrixDouble B;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixDoubleFromBuff(2, 3, aData.data(), aData.size(), A);
        unusedStat = createMatrixDouble(2, 3, B);

        MatrixDoubleView aView = getMatrixDoubleView(A);
        MatrixDoubleView bView = getMatrixDoubleView(B);
        mlt::math::mathStatus mulStat = multiplyScalarMatrixDouble(aView, mulConst, bView);

        assertEq(mulStat, mlt::math::MATH_SUCCESS, "Matrix scalar multiplication failed (double part).");

        for (size_t i = 0; i < aData.size(); ++i)
            assertEq(bView.data[i], aData[i] * mulConst, "Wrong value (double part).");

        deleteMatrixDouble(A);
        deleteMatrixDouble(B);
    }
}

static void matrixKernelAddScalarInPlaceTest()
{
    {
        constexpr float mulConst = 2.f;
        FloatVec aData = {1, 4, 2, 5, 3, 6};

        MatrixFloat A;
        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixFloatFromBuff(2, 3, aData.data(), aData.size(), A);

        MatrixFloatView aView = getMatrixFloatView(A);

        mlt::math::mathStatus mulStat = multiplyScalarMatrixFloatInPlace(aView, mulConst);

        assertEq(mulStat, mlt::math::MATH_SUCCESS, "Matrix scalar in place multiplication failed (float part).");

        for (size_t i = 0; i < aData.size(); ++i)
            assertEq(aView.data[i], aData[i] * mulConst, "Wrong value (float part).");

        deleteMatrixFloat(A);
    }

    {
        constexpr double mulConst = 2.;
        DoubleVec aData = {1, 4, 2, 5, 3, 6};

        MatrixDouble A;
        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixDoubleFromBuff(2, 3, aData.data(), aData.size(), A);

        MatrixDoubleView aView = getMatrixDoubleView(A);

        mlt::math::mathStatus mulStat = multiplyScalarMatrixDoubleInPlace(aView, mulConst);

        assertEq(mulStat, mlt::math::MATH_SUCCESS, "Matrix scalar in place multiplication failed (double part).");

        for (size_t i = 0; i < aData.size(); ++i)
            assertEq(aView.data[i], aData[i] * mulConst, "Wrong value (double part).");

        deleteMatrixDouble(A);
    }
}

static void matrixKernelSubtractTest()
{
    {
        constexpr size_t buffSize = 6;
        FloatVec buffA = {1, 2, 3, 4, 5, 6};
        FloatVec buffB = {6, 5, 4, 3, 2, 1};

        MatrixFloat A;
        MatrixFloat B;
        MatrixFloat C;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixFloatFromBuff(2, 3, buffA.data(), buffA.size(), A);
        unusedStat = createMatrixFloatFromBuff(2, 3, buffB.data(), buffB.size(), B);
        unusedStat = createMatrixFloat(2, 3, C);

        MatrixFloatView viewA = getMatrixFloatView(A);
        MatrixFloatView viewB = getMatrixFloatView(B);
        MatrixFloatView viewC = getMatrixFloatView(C);
        mlt::math::mathStatus addStat = subtractMatrixFloat(viewA, viewB, viewC);

        assertEq(addStat, mlt::math::MATH_SUCCESS, "Matrix shape was missmatched.");
        
        for (size_t i = 0; i < buffSize; i++)
            assertEq(C.data[i], buffA[i] - buffB[i], "Matrix subtraction failed.");


        deleteMatrixFloat(A);
        deleteMatrixFloat(B);
        deleteMatrixFloat(C);
    }

    {
        constexpr size_t buffSize = 6;
        DoubleVec buffA = {1, 2, 3, 4, 5, 6};
        DoubleVec buffB = {6, 5, 4, 3, 2, 1};

        MatrixDouble A;
        MatrixDouble B;
        MatrixDouble C;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixDoubleFromBuff(2, 3, buffA.data(), buffA.size(), A);
        unusedStat = createMatrixDoubleFromBuff(2, 3, buffB.data(), buffB.size(), B);
        unusedStat = createMatrixDouble(2, 3, C);

        MatrixDoubleView viewA = getMatrixDoubleView(A);
        MatrixDoubleView viewB = getMatrixDoubleView(B);
        MatrixDoubleView viewC = getMatrixDoubleView(C);
        mlt::math::mathStatus addStat = subtractMatrixDouble(viewA, viewB, viewC);

        assertEq(addStat, mlt::math::MATH_SUCCESS, "Matrix shape was missmatched.");
        
        for (size_t i = 0; i < buffSize; i++)
            assertEq(C.data[i], buffA[i] - buffB[i], "Matrix subtraction failed.");


        deleteMatrixDouble(A);
        deleteMatrixDouble(B);
        deleteMatrixDouble(C);
    }
}

static void matrixKernelSubtractInPlaceTest()
{
    {
        constexpr size_t buffSize = 6;
        FloatVec buffA = {1, 2, 3, 4, 5, 6};
        FloatVec buffB = {6, 5, 4, 3, 2, 1};

        MatrixFloat A;
        MatrixFloat B;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixFloatFromBuff(2, 3, buffA.data(), buffA.size(), A);
        unusedStat = createMatrixFloatFromBuff(2, 3, buffB.data(), buffB.size(), B);

        MatrixFloatView viewA = getMatrixFloatView(A);
        MatrixFloatView viewB = getMatrixFloatView(B);
        mlt::math::mathStatus addStat = subtractInPlaceMatrixFloat(viewA, viewB);

        assertEq(addStat, mlt::math::MATH_SUCCESS, "Matrix shape was missmatched.");
        
        for (size_t i = 0; i < buffSize; i++)
            assertEq(A.data[i], buffA[i] - buffB[i], "Matrix subtraction failed.");


        deleteMatrixFloat(A);
        deleteMatrixFloat(B);
    }

    {
        constexpr size_t buffSize = 6;
        DoubleVec buffA = {1, 2, 3, 4, 5, 6};
        DoubleVec buffB = {6, 5, 4, 3, 2, 1};

        MatrixDouble A;
        MatrixDouble B;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixDoubleFromBuff(2, 3, buffA.data(), buffA.size(), A);
        unusedStat = createMatrixDoubleFromBuff(2, 3, buffB.data(), buffB.size(), B);

        MatrixDoubleView viewA = getMatrixDoubleView(A);
        MatrixDoubleView viewB = getMatrixDoubleView(B);
        mlt::math::mathStatus addStat = subtractInPlaceMatrixDouble(viewA, viewB);

        assertEq(addStat, mlt::math::MATH_SUCCESS, "Matrix shape was missmatched.");
        
        for (size_t i = 0; i < buffSize; i++)
            assertEq(A.data[i], buffA[i] - buffB[i], "Matrix subtraction failed.");


        deleteMatrixDouble(A);
        deleteMatrixDouble(B);
    }
}

REGISTER_TEST(matrixKernelAddTest);
REGISTER_TEST(matrixKernelMultiplyTest);
REGISTER_TEST(matrixKernelCloneTest);
REGISTER_TEST(matrixKernelAddScalarTest);
REGISTER_TEST(matrixKernelAddScalarInPlaceTest);
REGISTER_TEST(matrixKernelSubtractTest);
REGISTER_TEST(matrixKernelSubtractInPlaceTest);
