#include "mlt/math/matrix.h"

#include "../testdef.h"

#include <stdio.h>
#include <stdlib.h>

void createMatrixTest() {
    const char* testName = "createMatrixTest";

    mltMatrixF* matF = NULL;
    mltStatus createStatF = mltFwMatrixFCreate(2, 3, &matF);
    ASSERT_STATUS_OK(testName, createStatF, "MatrixCreation failed.");

    mltMatrixD* matD = NULL;
    mltStatus createStatD = mltFwMatrixDCreate(2, 3, &matD);
    ASSERT_STATUS_OK(testName, createStatD, "MatrixCreation failed.");

cleanup:
    if (matF) mltFwMatrixFDestroy(matF);
    if (matD) mltFwMatrixDDestroy(matD);
}

void createMatrixFromBuffTest() {
    mltMatrixF* matF = NULL;
    mltMatrixD* matD = NULL;

    size_t rows = 2;
    size_t cols = 3;

    float* buffF = malloc(rows * cols * sizeof(float));
    double* buffD = malloc(rows * cols * sizeof(double));

    mltStatus createStatF = mltFwMatrixFCreateFromBuff(rows, cols, buffF, rows * cols, &matF);
    
    float valF00;
    mltStatus getStatF0 = mltFwMatrixFGet(matF, 0, 0, &valF00);
    ASSERT_EQ_FLOAT("createMatrixFromBuffTest", valF00, buffF[0], "Wrong value");

    float valF10;
    mltStatus getStatF1 = mltFwMatrixFGet(matF, 1, 0, &valF10);
    ASSERT_EQ_FLOAT("createMatrixFromBuffTest", valF10, buffF[1], "Wrong value");

    float valF11;
    mltStatus getStatF2 = mltFwMatrixFGet(matF, 1, 1, &valF11);
    ASSERT_EQ_FLOAT("createMatrixTest", valF11, buffF[3], "Wrong value");

    mltStatus createStatD = mltFwMatrixDCreateFromBuff(rows, cols, buffD, rows * cols, &matD);
    
    double valD00;
    mltStatus getStatD0 = mltFwMatrixDGet(matD, 0, 0, &valD00);
    ASSERT_EQ_FLOAT("createMatrixFromBuffTest", valD00, buffD[0], "Wrong value");

    double valD10;
    mltStatus getStatD1 = mltFwMatrixDGet(matD, 1, 0, &valD10);
    ASSERT_EQ_FLOAT("createMatrixFromBuffTest", valD10, buffD[1], "Wrong value");

    double valD11;
    mltStatus getStatD2 = mltFwMatrixDGet(matD, 1, 1, &valD11);
    ASSERT_EQ_FLOAT("createMatrixTest", valD11, buffD[3], "Wrong value");

cleanup:
    free(buffF);
    if (matF) mltFwMatrixFDestroy(matF);
    if (matD) mltFwMatrixDDestroy(matD);
}

void getAndSetMatrixTest() {
    mltMatrixF* matF = NULL;

    mltStatus createStatF = mltFwMatrixFCreate(2, 3, &matF);
    float valF;
    mltStatus getStatF = mltFwMatrixFGet(matF, 0, 0, &valF);

    ASSERT_EQ_FLOAT("getAndSetMatrixTest (float)", valF, 0.f, "Wrong value in getter");

    float setValF = 8.f;
    mltStatus setStatF = mltFwMatrixFSet(matF, 1, 1, setValF);

    float valF2;
    mltStatus getStatF2 = mltFwMatrixFGet(matF, 1, 1, &valF2);

    ASSERT_EQ_FLOAT("getAndSetMatrixTest (float)", valF2, setValF, "Wrong value in getter two.");

    mltMatrixD* matD = NULL;

    mltStatus createStatD = mltFwMatrixDCreate(2, 3, &matD);
    double valD;
    mltStatus getStatD = mltFwMatrixDGet(matD, 0, 0, &valD);

    ASSERT_EQ_DOUBLE("getAndSetMatrixTest (double)", valD, 0.0, "Wrong value in getter");

    double setValD = 8.0;
    mltStatus setStatD = mltFwMatrixDSet(matD, 1, 1, setValD);

    double valD2;
    mltStatus getStatD2 = mltFwMatrixDGet(matD, 1, 1, &valD2);

    ASSERT_EQ_DOUBLE("getAndSetMatrixTest (double)", valD2, setValD, "Wrong value in getter two.");

cleanup:
    if (matF) mltFwMatrixFDestroy(matF);
    if (matD) mltFwMatrixDDestroy(matD);
}

void shapeMatrixTest() {
    mltMatrixF* matF = NULL;
    size_t rowsF = 2;
    size_t colsF = 4;

    mltStatus createStatF = mltFwMatrixFCreate(rowsF, colsF, &matF);
    ASSERT_STATUS_OK("shapeMatrixTest (float)", createStatF, "MatrixCreation failed.");

    size_t gRowF, gColF;
    mltStatus rowStatF = mltFwMatrixFRowCount(matF, &gRowF);
    ASSERT_STATUS_OK("shapeMatrixTest (float)", rowStatF, "Failed to get row count.");

    mltStatus colStatF = mltFwMatrixFColCount(matF, &gColF);
    ASSERT_STATUS_OK("shapeMatrixTest (float)", colStatF, "Failed to get column count.");

    ASSERT_EQ_INT("shapeMatrixTest (float)", gRowF, rowsF, "Wrong row size.");
    ASSERT_EQ_INT("shapeMatrixTest (float)", gColF, colsF, "Wrong col size.");

    mltMatrixD* matD = NULL;
    size_t rowsD = 3;
    size_t colsD = 5;

    mltStatus createStatD = mltFwMatrixDCreate(rowsD, colsD, &matD);
    ASSERT_STATUS_OK("shapeMatrixTest (double)", createStatD, "MatrixCreation failed.");

    size_t gRowD, gColD;
    mltStatus rowStatD = mltFwMatrixDRowCount(matD, &gRowD);
    ASSERT_STATUS_OK("shapeMatrixTest (double)", rowStatD, "Failed to get row count.");

    mltStatus colStatD = mltFwMatrixDColCount(matD, &gColD);
    ASSERT_STATUS_OK("shapeMatrixTest (double)", colStatD, "Failed to get column count.");

    ASSERT_EQ_INT("shapeMatrixTest (double)", gRowD, rowsD, "Wrong row size.");
    ASSERT_EQ_INT("shapeMatrixTest (double)", gColD, colsD, "Wrong col size.");

cleanup:
    if (matF) mltFwMatrixFDestroy(matF);
    if (matD) mltFwMatrixDDestroy(matD);
}

void addMatrixTest() {
    const char* testName = "addMatrixTest";

    size_t rowsF = 2;
    size_t colsF = 3;
    size_t elemCountF = rowsF * colsF;
    float* buffAF = malloc(elemCountF * sizeof(float));
    float* buffBF = malloc(elemCountF * sizeof(float));

    for (size_t i = 0; i < elemCountF; ++i) buffAF[i] = (float)i;
    for (size_t i = 0; i < elemCountF; ++i) buffBF[i] = 2.f * (float)i;

    mltMatrixF* matAF = NULL;
    mltMatrixF* matBF = NULL;
    mltMatrixF* matCF = NULL;

    mltFwMatrixFCreateFromBuff(rowsF, colsF, buffAF, elemCountF, &matAF);
    mltFwMatrixFCreateFromBuff(rowsF, colsF, buffBF, elemCountF, &matBF);

    mltStatus addStatF = mltFwMatrixFAdd(matAF, matBF, &matCF);
    ASSERT_STATUS_OK(testName, addStatF, "Float addition failed.");

    float valF10;
    mltFwMatrixFGet(matCF, 1, 0, &valF10);
    ASSERT_EQ_FLOAT(testName, valF10, 3.f, "Wrong value in float matrix.");

    float valF02;
    mltFwMatrixFGet(matCF, 0, 2, &valF02);
    ASSERT_EQ_FLOAT(testName, valF02, 12.f, "Wrong value in float matrix.");

    size_t rowsD = 2;
    size_t colsD = 3;
    size_t elemCountD = rowsD * colsD;
    double* buffAD = malloc(elemCountD * sizeof(double));
    double* buffBD = malloc(elemCountD * sizeof(double));

    for (size_t i = 0; i < elemCountD; ++i) buffAD[i] = (double)i;
    for (size_t i = 0; i < elemCountD; ++i) buffBD[i] = 2.0 * (double)i;

    mltMatrixD* matAD = NULL;
    mltMatrixD* matBD = NULL;
    mltMatrixD* matCD = NULL;

    mltFwMatrixDCreateFromBuff(rowsD, colsD, buffAD, elemCountD, &matAD);
    mltFwMatrixDCreateFromBuff(rowsD, colsD, buffBD, elemCountD, &matBD);

    mltStatus addStatD = mltFwMatrixDAdd(matAD, matBD, &matCD);
    ASSERT_STATUS_OK(testName, addStatD, "Double addition failed.");

    double valD10;
    mltFwMatrixDGet(matCD, 1, 0, &valD10);
    ASSERT_EQ_DOUBLE(testName, valD10, 3.0, "Wrong value in double matrix.");

    double valD02;
    mltFwMatrixDGet(matCD, 0, 2, &valD02);
    ASSERT_EQ_DOUBLE(testName, valD02, 12.0, "Wrong value in double matrix.");

cleanup:
    if (buffAF) free(buffAF);
    if (buffBF) free(buffBF);
    if (matAF) mltFwMatrixFDestroy(matAF);
    if (matBF) mltFwMatrixFDestroy(matBF);
    if (matCF) mltFwMatrixFDestroy(matCF);

    if (buffAD) free(buffAD);
    if (buffBD) free(buffBD);
    if (matAD) mltFwMatrixDDestroy(matAD);
    if (matBD) mltFwMatrixDDestroy(matBD);
    if (matCD) mltFwMatrixDDestroy(matCD);
}

void addMatrixInPlaceTest() {
    const char* testName = "addMatrixInPlaceTest";

    size_t rowsF = 2;
    size_t colsF = 3;
    size_t elemCountF = rowsF * colsF;
    float* buffAF = malloc(elemCountF * sizeof(float));
    float* buffBF = malloc(elemCountF * sizeof(float));

    for (size_t i = 0; i < elemCountF; ++i) buffAF[i] = (float)i;
    for (size_t i = 0; i < elemCountF; ++i) buffBF[i] = 2.f * (float)i;

    mltMatrixF* matAF = NULL;
    mltMatrixF* matBF = NULL;

    mltFwMatrixFCreateFromBuff(rowsF, colsF, buffAF, elemCountF, &matAF);
    mltFwMatrixFCreateFromBuff(rowsF, colsF, buffBF, elemCountF, &matBF);

    mltStatus addStatF = mltFwMatrixFAddInPlace(matAF, matBF);
    ASSERT_STATUS_OK(testName, addStatF, "Float in-place addition failed.");

    float valF10;
    mltFwMatrixFGet(matAF, 1, 0, &valF10);
    ASSERT_EQ_FLOAT(testName, valF10, 3.f, "Wrong value in float matrix.");

    float valF02;
    mltFwMatrixFGet(matAF, 0, 2, &valF02);
    ASSERT_EQ_FLOAT(testName, valF02, 12.f, "Wrong value in float matrix.");

    size_t rowsD = 2;
    size_t colsD = 3;
    size_t elemCountD = rowsD * colsD;
    double* buffAD = malloc(elemCountD * sizeof(double));
    double* buffBD = malloc(elemCountD * sizeof(double));

    for (size_t i = 0; i < elemCountD; ++i) buffAD[i] = (double)i;
    for (size_t i = 0; i < elemCountD; ++i) buffBD[i] = 2.0 * (double)i;

    mltMatrixD* matAD = NULL;
    mltMatrixD* matBD = NULL;

    mltFwMatrixDCreateFromBuff(rowsD, colsD, buffAD, elemCountD, &matAD);
    mltFwMatrixDCreateFromBuff(rowsD, colsD, buffBD, elemCountD, &matBD);

    mltStatus addStatD = mltFwMatrixDAddInPlace(matAD, matBD);
    ASSERT_STATUS_OK(testName, addStatD, "Double in-place addition failed.");

    double valD10;
    mltFwMatrixDGet(matAD, 1, 0, &valD10);
    ASSERT_EQ_DOUBLE(testName, valD10, 3.0, "Wrong value in double matrix.");

    double valD02;
    mltFwMatrixDGet(matAD, 0, 2, &valD02);
    ASSERT_EQ_DOUBLE(testName, valD02, 12.0, "Wrong value in double matrix.");

cleanup:
    if (buffAF) free(buffAF);
    if (buffBF) free(buffBF);
    if (matAF) mltFwMatrixFDestroy(matAF);
    if (matBF) mltFwMatrixFDestroy(matBF);

    if (buffAD) free(buffAD);
    if (buffBD) free(buffBD);
    if (matAD) mltFwMatrixDDestroy(matAD);
    if (matBD) mltFwMatrixDDestroy(matBD);
}

void multiplyMatrixTest() {
    const char* testName = "multiplyMatrixTest";

    mltMatrixF *matA = NULL, *matB = NULL, *matC = NULL;
    mltMatrixD *matAD = NULL, *matBD = NULL, *matCD = NULL;

    size_t rowsA = 2, colsA = 3;
    size_t rowsB = 3, colsB = 2;

    float buffA[] = {
        1,2,3,
        4,5,6
    };

    float buffB[] = {
        1,2,
        3,4,
        5,6
    };

    float expected[] = {
        22,49,
        28,64
    };

    mltFwMatrixFCreateFromBuff(rowsA, colsA, buffA, 6, &matA);
    mltFwMatrixFCreateFromBuff(rowsB, colsB, buffB, 6, &matB);

    mltStatus stat = mltFwMatrixFMultiply(matA, matB, &matC);
    ASSERT_STATUS_OK(testName, stat, "Float multiplication failed.");

    for (size_t r = 0; r < rowsA; ++r) {
        for (size_t c = 0; c < colsB; ++c) {
            float val;
            mltFwMatrixFGet(matC, r, c, &val);
            ASSERT_EQ_FLOAT(testName, val, expected[r*colsB +c], "Float multiply wrong value.");
        }
    }


    double buffAD[] = {
        1,2,3,
        4,5,6
    };

    double buffBD[] = {
        1,2,
        3,4,
        5,6
    };

    double expectedD[] = {
        22,28,
        49,64
    };

    mltFwMatrixDCreateFromBuff(rowsA, colsA, buffAD, 6, &matAD);
    mltFwMatrixDCreateFromBuff(rowsB, colsB, buffBD, 6, &matBD);

    stat = mltFwMatrixDMultiply(matAD, matBD, &matCD);
    ASSERT_STATUS_OK(testName, stat, "Double multiplication failed.");

    for (size_t r = 0; r < rowsA; ++r) {
        for (size_t c = 0; c < colsB; ++c) {
            double val;
            mltFwMatrixDGet(matCD, r, c, &val);
            ASSERT_EQ_DOUBLE(testName, val, expectedD[c*rowsA+r], "Double multiply wrong value.");
        }
    }

cleanup:
    if (matA)  mltFwMatrixFDestroy(matA);
    if (matB)  mltFwMatrixFDestroy(matB);
    if (matC)  mltFwMatrixFDestroy(matC);

    if (matAD) mltFwMatrixDDestroy(matAD);
    if (matBD) mltFwMatrixDDestroy(matBD);
    if (matCD) mltFwMatrixDDestroy(matCD);
}

void cloneMatrixTest() {
    const char* testName = "cloneMatrixTest";

    size_t rowsF = 2, colsF = 3;
    size_t elemCountF = rowsF * colsF;
    float* buffF = malloc(elemCountF * sizeof(float));
    for (size_t i = 0; i < elemCountF; ++i) buffF[i] = (float)(i + 1);

    mltMatrixF *matF = NULL, *matFClone = NULL;
    mltFwMatrixFCreateFromBuff(rowsF, colsF, buffF, elemCountF, &matF);

    mltStatus stat = mltFwMatrixFClone(matF, &matFClone);
    ASSERT_STATUS_OK(testName, stat, "Float clone failed.");

    // Prüfe alle Elemente
    for (size_t r = 0; r < rowsF; ++r) {
        for (size_t c = 0; c < colsF; ++c) {
            float val;
            mltFwMatrixFGet(matFClone, r, c, &val);
            ASSERT_EQ_FLOAT(testName, val, buffF[c*rowsF + r], "Float clone value mismatch");
        }
    }

    size_t rowsD = 2, colsD = 3;
    size_t elemCountD = rowsD * colsD;
    double* buffD = malloc(elemCountD * sizeof(double));
    for (size_t i = 0; i < elemCountD; ++i) buffD[i] = (double)(i + 1);

    mltMatrixD *matD = NULL, *matDClone = NULL;
    mltFwMatrixDCreateFromBuff(rowsD, colsD, buffD, elemCountD, &matD);

    stat = mltFwMatrixDClone(matD, &matDClone);
    ASSERT_STATUS_OK(testName, stat, "Double clone failed.");

    for (size_t r = 0; r < rowsD; ++r) {
        for (size_t c = 0; c < colsD; ++c) {
            double val;
            mltFwMatrixDGet(matDClone, r, c, &val);
            ASSERT_EQ_DOUBLE(testName, val, buffD[c*rowsD + r], "Double clone value mismatch");
        }
    }

cleanup:
    if (buffF) free(buffF);
    if (buffD) free(buffD);
    if (matF) mltFwMatrixFDestroy(matF);
    if (matFClone) mltFwMatrixFDestroy(matFClone);
    if (matD) mltFwMatrixDDestroy(matD);
    if (matDClone) mltFwMatrixDDestroy(matDClone);
}

void copyMatrixTest() {
    const char* testName = "copyMatrixTest";

    size_t rowsF = 2, colsF = 3;
    float buffF[] = {1.f, 2.f, 3.f, 4.f, 5.f, 6.f};
    mltMatrixF *matF = NULL, *matFCopy = NULL;
    mltFwMatrixFCreateFromBuff(rowsF, colsF, buffF, rowsF*colsF, &matF);

    mltStatus stat = mltFwMatrixFCopy(matF, &matFCopy);
    ASSERT_STATUS_OK(testName, stat, "Float copy failed.");

    for (size_t r = 0; r < rowsF; ++r) {
        for (size_t c = 0; c < colsF; ++c) {
            float val;
            mltFwMatrixFGet(matFCopy, r, c, &val);
            ASSERT_EQ_FLOAT(testName, val, buffF[c*rowsF + r], "Float copy value mismatch");
        }
    }

    size_t rowsD = 2, colsD = 3;
    double buffD[] = {1., 2., 3., 4., 5., 6.};
    mltMatrixD *matD = NULL, *matDCopy = NULL;
    mltFwMatrixDCreateFromBuff(rowsD, colsD, buffD, rowsD*colsD, &matD);

    stat = mltFwMatrixDCopy(matD, &matDCopy);
    ASSERT_STATUS_OK(testName, stat, "Double copy failed.");

    for (size_t r = 0; r < rowsD; ++r) {
        for (size_t c = 0; c < colsD; ++c) {
            double val;
            mltFwMatrixDGet(matDCopy, r, c, &val);
            ASSERT_EQ_DOUBLE(testName, val, buffD[c*rowsD + r], "Double copy value mismatch");
        }
    }

cleanup:
    if (matF) mltFwMatrixFDestroy(matF);
    if (matFCopy) mltFwMatrixFDestroy(matFCopy);
    if (matD) mltFwMatrixDDestroy(matD);
    if (matDCopy) mltFwMatrixDDestroy(matDCopy);
}

void submatrixMatrixTest() {
    const char* testName = "submatrixMatrixTest";

    size_t rowsF = 3, colsF = 3;
    float buffF[] = {1.f,2.f,3.f,4.f,5.f,6.f,7.f,8.f,9.f};
    mltMatrixF *matF = NULL, *subF = NULL;
    mltFwMatrixFCreateFromBuff(rowsF, colsF, buffF, rowsF*colsF, &matF);

    mltStatus stat = mltFwMatrixFSubmatrix(matF, 1, 1, 2, 2, &subF);
    ASSERT_STATUS_OK(testName, stat, "Float submatrix failed.");

    float expectedF[] = {5.f, 6.f, 8.f, 9.f};
    for (size_t r = 0; r < 2; ++r) {
        for (size_t c = 0; c < 2; ++c) {
            float val;
            mltFwMatrixFGet(subF, r, c, &val);
            ASSERT_EQ_FLOAT(testName, val, expectedF[c*2 + r], "Float submatrix value mismatch");
        }
    }

    size_t rowsD = 3, colsD = 3;
    double buffD[] = {1.,2.,3.,4.,5.,6.,7.,8.,9.};
    mltMatrixD *matD = NULL, *subD = NULL;
    mltFwMatrixDCreateFromBuff(rowsD, colsD, buffD, rowsD*colsD, &matD);

    stat = mltFwMatrixDSubmatrix(matD, 1, 1, 2, 2, &subD);
    ASSERT_STATUS_OK(testName, stat, "Double submatrix failed.");

    double expectedD[] = {5.,6.,8.,9.};
    for (size_t r = 0; r < 2; ++r) {
        for (size_t c = 0; c < 2; ++c) {
            double val;
            mltFwMatrixDGet(subD, r, c, &val);
            ASSERT_EQ_DOUBLE(testName, val, expectedD[c*2 + r], "Double submatrix value mismatch");
        }
    }

cleanup:
    if (matF) mltFwMatrixFDestroy(matF);
    if (subF) mltFwMatrixFDestroy(subF);
    if (matD) mltFwMatrixDDestroy(matD);
    if (subD) mltFwMatrixDDestroy(subD);
}


int main(void) {
    createMatrixTest();
    createMatrixFromBuffTest();
    getAndSetMatrixTest();
    shapeMatrixTest();
    addMatrixTest();
    addMatrixInPlaceTest();
    multiplyMatrixTest();
    cloneMatrixTest();
    copyMatrixTest();
    submatrixMatrixTest();

    printf("Ran all tests.\n");
}
