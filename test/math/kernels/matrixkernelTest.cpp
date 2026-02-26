#include "../../testdef.hpp"
#include "math/datastructures/matrixview.hpp"
#include "math/mathstatus.hpp"

#include <math/datastructures/matrix.hpp>
#include <math/kernels/matrixkernels.hpp>
#include <vector>

using namespace mlt::math::datastructures;
using namespace mlt::math::kernels;
using FloatVec = std::vector<float>;

static void matrixKernelAddTest()
{
    FloatVec sumOne = {1, 2, 3, 4, 5, 6};
    FloatVec sumTwo = {6, 5, 4, 3, 2, 1};

    MatrixFloat matOne;
    MatrixFloat matTwo;
    MatrixFloat matResult;

    createMatrixFloatFromBuff(2, 3, sumOne.data(), sumOne.size(), matOne);
    createMatrixFloatFromBuff(2, 3, sumTwo.data(), sumTwo.size(), matTwo);
    createMatrixFloat(2, 3, matResult);

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


REGISTER_TEST(matrixKernelAddTest);
