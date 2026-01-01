#include "../../testdef.hpp"
#include <MLTooling.h>

#include <vector>

using namespace Container;
using FloatVec = std::vector<float>;

static void testConstructorAndGetRow()
{
    FloatVec data = {1, 2, 3, 4, 5, 6};
    Mat m(2, 3, data);

    assertEq(m.getShape().rows, static_cast<size_t>(2), "Failed matrix creation.");
    assertEq(m.getShape().cols, static_cast<size_t>(3), "Failed matrix creation.");

    FloatVec row0 = m.getRow(0);
    FloatVec row1 = m.getRow(1);
    assertEq(row0, {1, 2, 3}, "Failed getting row.");
    assertEq(row1, {4, 5, 6}, "Failed getting row.");

    assertEq(m(0, 0), 1, "Failed getting item.");
    assertEq(m(1, 2), 6, "Failed getting item.");

    m(0, 1) = 10;
    assertEq(m(0, 1), 10, "Failed setting item.");
}

static void testAddRow()
{
    Mat m(2, 2, 0.f);
    FloatVec newRow = {1.f, 2.f};
    m.addRow(newRow);

    assertEq(m.getShape().rows, static_cast<size_t>(3), "Failed adding row.");

    FloatVec row = m.getRow(2);
    assertEq(row[0], 1.f, "Failed adding correct row.");
    assertEq(row[1], 2.f, "Failed adding correct row.");
}

static void testAdditionOperators()
{
    Mat a(2, 2, FloatVec{1, 2, 3, 4});
    Mat b(2, 2, FloatVec{5, 6, 7, 8});

    a += b;
    assertEq(a.getRow(0), {6, 8}, "Failed matrix in place addition.");
    assertEq(a.getRow(1), {10, 12}, "Failed matrix in place addition.");

    Mat c = a + b;
    assertEq(c.getRow(0), {11, 14}, "Failed matrix addition.");
    assertEq(c.getRow(1), {17, 20}, "Failed matrix addition.");
}

static void testMultiplicationOperator()
{
    Mat a(2, 3, FloatVec{1, 2, 3, 4, 5, 6});
    Mat b(3, 2, FloatVec{7, 8, 9, 10, 11, 12});

    Mat c = a * b;
    assertEq(c.getRow(0), {58, 64}, "Failed matrix multiplication.");
    assertEq(c.getRow(1), {139, 154}, "Failed matrix multiplication.");
}

REGISTER_TEST(testConstructorAndGetRow);
REGISTER_TEST(testAddRow);
REGISTER_TEST(testAdditionOperators);
REGISTER_TEST(testMultiplicationOperator);