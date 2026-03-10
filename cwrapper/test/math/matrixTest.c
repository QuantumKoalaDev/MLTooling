#include "mlt/math/matrix.h"

#include "../testdef.h"

#include <stdio.h>
#include <stdlib.h>

void createMatrixTest() {
    mltMatrixF* mat = NULL;
    
    mltStatus createStat = mltFwMatrixFCreate(2, 3, &mat);
    ASSERT_STATUS_OK("createMatrixTest", createStat, "MatrixCreation failed.");

cleanup:
    if (mat)
        mltFwMatrixFDestroy(mat);
}

void createMatrixFromBuffTest() {
    mltMatrixF* mat = NULL;

    size_t rows = 2;
    size_t cols = 3;

    float* buff = malloc(rows * cols * sizeof(float));

    mltStatus createStat = mltFwMatrixFCreateFromBuff(rows, cols, buff, rows * cols, &mat);
    
    float val00;
    mltStatus getStat0 = mltFwMatrixFGet(mat, 0, 0, &val00);
    ASSERT_EQ_FLOAT("createMatrixFromBuffTest", val00, buff[0], "Wrong value");

    float val10;
    mltStatus getStat1 = mltFwMatrixFGet(mat, 1, 0, &val10);
    ASSERT_EQ_FLOAT("createMatrixFromBuffTest", val10, buff[1], "Wrong value");

    float val11;
    mltStatus getStat2 = mltFwMatrixFGet(mat, 1, 1, &val11);
    ASSERT_EQ_FLOAT("createMatrixTest", val11, buff[3], "Wrong value");

cleanup:
    free(buff);
    mltFwMatrixFDestroy(mat);
}

void getAndSetMatrixTest() {
    mltMatrixF* mat = NULL;

    mltStatus createStat = mltFwMatrixFCreate(2, 3, &mat);
    float val;
    mltStatus getStat = mltFwMatrixFGet(mat, 0, 0, &val);

    ASSERT_EQ_FLOAT("getAndSetMatrixTest", val, 0.f, "Wrong value in getter");

    float setVal = 8.f;
    mltStatus setStat = mltFwMatrixFSet(mat, 1, 1, setVal);

    float val2;
    mltStatus getStat2 = mltFwMatrixFGet(mat, 1, 1, &val2);

    ASSERT_EQ_FLOAT("getAndSetMatrixTest", val2, setVal, "Wrong value in getter two.");

cleanup:
    mltFwMatrixFDestroy(mat);
}

void shapeMatrixTest() {
    mltMatrixF* mat = NULL;

    size_t rows = 2;
    size_t cols = 4;
    
    mltStatus createStat = mltFwMatrixFCreate(rows, cols, &mat);
    ASSERT_STATUS_OK("shapeMatrixTest", createStat, "MatrixCreation failed.");

    size_t gRow;
    size_t gCol;
    mltFwMatrixFRowCount(mat, &gRow);
    mltFwMatrixFColCount(mat, &gCol);
    
    ASSERT_EQ_INT("shapeMatrixTest", gRow, rows, "Wrong row size.");
    ASSERT_EQ_INT("shapeMatrixTest", gCol, gCol, "Wrong col size.");

cleanup:
    mltFwMatrixFDestroy(mat);
}

void addMatrixTest() {
    const char* testName = "addMatrixTest\0";
    size_t rows = 2;
    size_t cols = 3;
    size_t elemCount = rows * cols;
    float* buffA = malloc(rows * cols * sizeof(float));
    float* buffB = malloc(rows * cols * sizeof(float));
        
    for (size_t i = 0; i < rows * cols; ++i)
        buffA[i] = i;
        
    for (size_t i = 0; i < rows * cols; ++i)
        buffB[i] = 2 * i;

    mltMatrixF* matA = NULL;
    mltMatrixF* matB = NULL;
    mltMatrixF* matC = NULL;

    mltFwMatrixFCreateFromBuff(rows, cols, buffA, elemCount, &matA);
    mltFwMatrixFCreateFromBuff(rows, cols, buffB, elemCount, &matB);
    mltStatus addStat = mltFwMatrixFAdd(matA, matB, &matC);
    ASSERT_STATUS_OK(testName, addStat, "Addition failed.");

    float val10;
    mltFwMatrixFGet(matC, 1, 0, &val10);
    ASSERT_EQ_FLOAT(testName, val10, 3, "Wrong value.");

    float val02;
    mltFwMatrixFGet(matC, 0, 2, &val02);
    ASSERT_EQ_FLOAT(testName, val02, 12, "Wrong value.");
    

cleanup:
    free(buffA);
    free(buffB);
    mltFwMatrixFDestroy(matA);
    mltFwMatrixFDestroy(matB);
}

void addMatrixInPlaceTest() {
    const char* testName = "addMatrixInPlaceTest\0";
    size_t rows = 2;
    size_t cols = 3;
    size_t elemCount = rows * cols;
    float* buffA = malloc(elemCount * sizeof(float));
    float* buffB = malloc(elemCount * sizeof(float));

    for (size_t i = 0; i < elemCount; ++i)
        buffA[i] = i;

    for (size_t i = 0; i < elemCount; ++i)
        buffB[i] = i * 2;

    mltMatrixF* matA = NULL;
    mltMatrixF* matB = NULL;

    mltFwMatrixFCreateFromBuff(rows, cols, buffA, elemCount, &matA);
    mltFwMatrixFCreateFromBuff(rows, cols, buffB, elemCount, &matB);

    mltStatus addStat = mltFwMatrixFAddInPlace(matA, matB);
    ASSERT_STATUS_OK(testName, addStat, "In place addition failed.");

    float val10;
    mltFwMatrixFGet(matA, 1, 0, &val10);
    ASSERT_EQ_FLOAT(testName, val10, 3, "Wrong value.");

    float val02;
    mltFwMatrixFGet(matA, 0, 2, &val02);
    ASSERT_EQ_FLOAT(testName, val02, 12, "Wrong value.");

cleanup:
    free(buffA);
    free(buffB);
    mltFwMatrixFDestroy(matA);
    mltFwMatrixFDestroy(matB);
}


int main(void) {
    createMatrixTest();
    createMatrixFromBuffTest();
    getAndSetMatrixTest();
    shapeMatrixTest();
    addMatrixTest();
    addMatrixInPlaceTest();

    printf("Ran all tests.\n");
}
