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
    mlt::math::mathStatus addStat =  addMatrixFloat(oneView, twoView, resultView);

    assertEq(addStat, mlt::math::MATH_SUCCESS, "Matrix shape was missmatched.");
    assertEq(resultView.data[0], 7.f, "Matrix addition failed.");


    deleteMatrixFloat(matOne);
    deleteMatrixFloat(matOne);
    deleteMatrixFloat(matResult);
}

static void matrixKernelMultiplyTest()
{
    {
        FloatVec aData = { 1, 4, 2, 5, 3, 6 };
        FloatVec bData = { 7, 8, 9, 10, 11, 12 };
        FloatVec cData = { 50, 122, 68, 167 };

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
        DoubleVec aData = { 1, 4, 2, 5, 3, 6 };
        DoubleVec bData = { 7, 8, 9, 10, 11, 12 };
        DoubleVec cData = {50, 122, 68, 167 };

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
        FloatVec aData = { 1, 4, 2, 5, 3, 6 };
        
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
        DoubleVec aData = { 1, 4, 2, 5, 3, 6 };

        MatrixDouble A;
        MatrixDouble B;

        mlt::math::mathStatus unusedStat;
        unusedStat = createMatrixDoubleFromBuff(2, 3, aData.data(), aData.size(), A);
        unusedStat = createMatrixDouble(2, 3, B);

        MatrixDoubleView aView = getMatrixDoubleView(A);
        MatrixDoubleView bView = getMatrixDoubleView(B);

        mlt::math::mathStatus cloneStat = cloneMatrixDouble(aView, bView);

        assertEq(cloneStat, mlt::math::MATH_SUCCESS, "Matrix could not be cloned due to shape missmatch (double part).");

        for (size_t i = 0; i < aData.size(); ++i)
            assertEq(bView.data[i], aData[i], "Wrong value (double part).");

        deleteMatrixDouble(A);
        deleteMatrixDouble(B);
    }
}


REGISTER_TEST(matrixKernelAddTest);
REGISTER_TEST(matrixKernelMultiplyTest);
REGISTER_TEST(matrixKernelCloneTest);
