#include "../../testdef.hpp"

#include <mlt/macros.hpp>

#include <span>

import mlt.core.error;
import mlt.internal.compute.operations;
import mlt.internal.compute.core.mltarray;
import mlt.internal.compute.core.sizearray;

using namespace mlt::core;
using namespace mlt::compute::ops;
using namespace mlt::compute::core;

#define ERROR(var) var.error().msg.data()

constexpr float aData[] = {
    1.f, 2.f, 3.f,
    4.f, 5.f, 6.f
};

constexpr float bData[] = {
    7.f, 8.f,
    9.f, 10.f,
    11.f, 12.f
};

void testOperationsMatmul()
{
    DefaultSizeArray aShape = DefaultSizeArray({2, 3});
    DefaultSizeArray bShape = DefaultSizeArray({3, 2});
    MltArray a = MLT_MOVE_VALUE(MltArray::from(std::span<const float>(aData), aShape));
    MltArray b = MLT_MOVE_VALUE(MltArray::from(std::span<const float>(bData), bShape));

    MltArray result = MLT_MOVE_VALUE(matmul(a, b));

    assertEq(result.shape.size(), (size_t)2, "Wrong shape size");
    assertEq(result.shape[0], (size_t)2, "Wrong row shape");
    assertEq(result.shape[1], (size_t)2, "Wrong col shape");

    const float* C = reinterpret_cast<const float*>(result.data->data);

    assertEq(C[0], 58.f, "Wrong value[0,0]");
    assertEq(C[1], 64.f, "Wrong value [0,1]");
    assertEq(C[2], 139.f, "Wrong value [1,0]");
    assertEq(C[3], 154.f, "Wrong value [1,1]");
}

void testOperationsMatmulTransposed()
{
    DefaultSizeArray aShape = DefaultSizeArray({2, 3});
    DefaultSizeArray bShape = DefaultSizeArray({2, 3});

    Result<MltArray> cA = MltArray::from(std::span<const float>(aData), aShape);
    Result<MltArray> cB = MltArray::from(std::span<const float>(bData), bShape);

    if (!cA)
        throwCustomMessage({ERROR(cA)});
    
    if (!cB)
        throwCustomMessage({ERROR(cB)});

    MltArray a = MLT_MOVE_VALUE(cA);
    MltArray b = MLT_MOVE_VALUE(cB);

    Result<MltArray> cBTrans = b.transpose();

    if (!cBTrans)
        throwCustomMessage({ERROR(cBTrans)});
    
    MltArray bTrans = MLT_MOVE_VALUE(cBTrans);

    Result<MltArray> cResult = matmul(a, bTrans);

    if (!cResult)
        throwCustomMessage({ERROR(cResult)});
    
    MltArray result = MLT_MOVE_VALUE(cResult);

    assertEq(result.shape.size(), (size_t)2, "Wrong shape size");
    assertEq(result.shape[0], (size_t)2, "Wrong row shape");
    assertEq(result.shape[1], (size_t)2, "Wrong col shape");

    const float* C = reinterpret_cast<const float*>(result.data->data);

    assertEq(C[0], 58.f, "Wrong value[0,0]");
    assertEq(C[1], 64.f, "Wrong value [0,1]");
    assertEq(C[2], 139.f, "Wrong value [1,0]");
    assertEq(C[3], 154.f, "Wrong value [1,1]");
}

REGISTER_TEST(testOperationsMatmul);
REGISTER_TEST(testOperationsMatmulTransposed);
