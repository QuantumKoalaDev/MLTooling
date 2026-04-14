#include "../../testdef.hpp"
#include <mlt/math/Matrix.hpp>
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

static void testConstructorMatrix()
{
    // Test for 1x1
    {
        Matrix<float> mat(1, 1);
        const float val = mat[0, 0];

        assertEq(val, 0.f, "Default Matrix construction failed.");

        std::vector<float> vec = {5.f};
        Matrix<float> matBuff(1, 1, vec);
        const float valBuff = matBuff[0, 0];

        assertEq(valBuff, vec[0], "Default matrix construction with buffer failed.");
    }

    // Test for 5x7
    {
        Matrix<float> mat(5, 7);
        const float val = mat[1, 2];
        assertEq(val, 0.f, "Default Matrix construction failed.");

        std::vector<float> buff = getTestVec(35, 4.f);
        Matrix<float> matBuff(5, 7, buff);

        const float testValOne = matBuff[0, 0];
        assertEq(testValOne, buff[0], "Col major layout broke.");
        assertEq(matBuff[4, 6], buff[34], "Col major layout broke.");
        assertEq(matBuff[3, 6], buff[33], "Col major layout broke.");
        assertEq(matBuff[1, 0], buff[1], "Col major layout broke.");
    }
}

static void testGetSetOperatorMatrix()
{
    // Test for 5x7
    {
        std::vector<float> buff = getTestVec(35, 5.f);
        Matrix<float> mat(5, 7, buff);

        mat[2, 4] = 24.f;
        assertEq(mat[2, 4], 24.f, "Value was not set.");
    }
}

static void testAdditionOperatorMatrix()
{
    // Test for 5x7 float
    {
        const std::vector<float> buffA = getTestVec(35, 4.f);
        const std::vector<float> buffB = getTestVec(35, 5.f);
        Matrix<float> A = Matrix(5, 7, std::span<const float>(buffA));
        Matrix<float> B = Matrix(5, 7, std::span<const float>(buffB));
        Matrix<float> C = A + B;

        assertEq(C[0, 0], buffA[0] + buffB[0], "Addition failed.");
        assertEq(C[4, 6], buffA[34] + buffB[34], "Addition failed.");
        assertEq(C[3, 6], buffA[33] + buffB[33], "Addition failed.");
    }

    // Test for 5x7 double
    {
        const std::vector<double> buffA = getTestVec(35, 4.9);
        const std::vector<double> buffB = getTestVec(35, 8.4);
        Matrix<double> A = Matrix(5, 7, std::span<const double>(buffA));
        Matrix<double> B = Matrix(5, 7, std::span<const double>(buffB));
        Matrix<double> C = A + B;

        assertEq(C[0, 0], buffA[0] + buffB[0], "Addition failed.");
        assertEq(C[4, 6], buffA[34] + buffB[34], "Addition failed.");
        assertEq(C[3, 6], buffA[33] + buffB[33], "Addition failed.");
    }
}

static void testMultiplicationOperatorMatrix()
{
    {
        const std::vector<float> buffA = {1, 4, 2, 5, 3, 6};
        const std::vector<float> buffB = {7, 8, 9, 10, 11, 12};
        const std::vector<float> buffC = {50, 122, 68, 167};

        Matrix<float> A = Matrix(2, 3, std::span<const float>(buffA));
        Matrix<float> B = Matrix(3, 2, std::span<const float>(buffB));
        Matrix<float> C = A * B;

        assertEq(C[0, 0], buffC[0], "Multiplication failed.");
        assertEq(C[1, 0], buffC[1], "Multiplication failed.");
        assertEq(C[0, 1], buffC[2], "Multiplication failed.");
        assertEq(C[1, 1], buffC[3], "Multiplication failed.");
    }

    {
        const std::vector<double> buffA = {1, 4, 2, 5, 3, 6};
        const std::vector<double> buffB = {7, 8, 9, 10, 11, 12};
        const std::vector<double> buffC = {50, 122, 68, 167};

        Matrix<double> A = Matrix(2, 3, std::span<const double>(buffA));
        Matrix<double> B = Matrix(3, 2, std::span<const double>(buffB));
        Matrix<double> C = A * B;

        assertEq(C[0, 0], buffC[0], "Multiplication failed.");
        assertEq(C[1, 0], buffC[1], "Multiplication failed.");
        assertEq(C[0, 1], buffC[2], "Multiplication failed.");
        assertEq(C[1, 1], buffC[3], "Multiplication failed.");
    }

    // Tests for matrix-vector multiplication
    {
        const std::vector<float> buffA = {1, 4, 2, 5, 3, 6};
        const std::vector<float> buffV = {7, 8, 9};
        const std::vector<float> resultBuff = {50, 122};

        Matrix<float> A = Matrix(2, 3, std::span<const float>(buffA));
        Vector<float> v = Vector(std::span<const float>(buffV));

        Vector<float> vm = A * v;

        assertEq(vm[0], resultBuff[0], "Matrix vector multiplication failed (float part).");
        assertEq(vm[1], resultBuff[1], "Matrix vector multiplication failed. (float part).");
    }

    {
        const std::vector<double> buffA = {1, 4, 2, 5, 3, 6};
        const std::vector<double> buffV = {7, 8, 9};
        const std::vector<double> resultBuff = {50, 122};

        Matrix<double> A = Matrix(2, 3, std::span<const double>(buffA));
        Vector<double> v = Vector(std::span<const double>(buffV));

        Vector<double> vm = A * v;

        assertEq(vm[0], resultBuff[0], "Matrix vector multiplication failed (double part).");
        assertEq(vm[1], resultBuff[1], "Matrix vector multiplication failed. (double part).");
    }
}

static void testCloneMatrix()
{
    {
        const std::vector<float> buffA = {1, 4, 2, 5, 3, 6};

        Matrix<float> A = Matrix(2, 3, std::span<const float>(buffA));
        Matrix<float> B = A.clone();

        assertEq(B[0, 0], buffA[0], "Clone failed (float part).");
        assertEq(B[1, 0], buffA[1], "Clone failed (float part).");
        assertEq(B[0, 1], buffA[2], "Clone failed (float part).");
        assertEq(B[1, 1], buffA[3], "Clone failed (float part).");
    }

    {
        const std::vector<double> buffA = {1, 4, 2, 5, 3, 6};

        Matrix<double> A = Matrix(2, 3, std::span<const double>(buffA));
        Matrix<double> B = A.clone();

        assertEq(B[0, 0], buffA[0], "Clone failed (float part).");
        assertEq(B[1, 0], buffA[1], "Clone failed (float part).");
        assertEq(B[0, 1], buffA[2], "Clone failed (float part).");
        assertEq(B[1, 1], buffA[3], "Clone failed (float part).");
    }
}

static void testSubmatrixMatrix()
{
    {
        const std::vector<float> buffA = {1, 4, 2, 5, 3, 6};

        Matrix<float> A = Matrix(2, 3, std::span<const float>(buffA));
        Matrix<float> B = A.submatrix(0, 1, 2, 2);

        assertEq(B[0, 0], buffA[2], "Submatrix failed (float part).");
        assertEq(B[1, 0], buffA[3], "Submatrix failed (float part).");
        assertEq(B[0, 1], buffA[4], "Submatrix failed (float part).");
        assertEq(B[1, 1], buffA[5], "Submatrix failed (float part).");
    }

    {
        const std::vector<double> buffA = {1, 4, 2, 5, 3, 6};

        Matrix<double> A = Matrix(2, 3, std::span<const double>(buffA));
        Matrix<double> B = A.submatrix(0, 1, 2, 2);

        assertEq(B[0, 0], buffA[2], "Submatrix failed (double part).");
        assertEq(B[1, 0], buffA[3], "Submatrix failed (double part).");
        assertEq(B[0, 1], buffA[4], "Submatrix failed (double part).");
        assertEq(B[1, 1], buffA[5], "Submatrix failed (double part).");
    }
}

REGISTER_TEST(testConstructorMatrix);
REGISTER_TEST(testGetSetOperatorMatrix);
REGISTER_TEST(testAdditionOperatorMatrix);
REGISTER_TEST(testMultiplicationOperatorMatrix);
REGISTER_TEST(testCloneMatrix);
REGISTER_TEST(testSubmatrixMatrix);
