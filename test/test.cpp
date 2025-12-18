#include <iostream>
#include <cassert>
#include <vector>

#include <MLTooling.h>

using namespace Container;
using FloatVec = std::vector<float>;


bool vecEqual(const std::vector<float>& a, const std::vector<float>& b, float tol = 1e-6f) {
    if (a.size() != b.size()) return false;
    for (size_t i = 0; i < a.size(); ++i)
        if (std::abs(a[i] - b[i]) > tol) return false;
    return true;
}

void testConstructorAndGetRow() {
    FloatVec data = { 1, 2, 3, 4, 5, 6 };
    Mat m(2, 3, data);

    assert(m.getShape().rows == 2);
    assert(m.getShape().cols == 3);

    // getRow
    FloatVec row0 = m.getRow(0);
    FloatVec row1 = m.getRow(1);
    assert(vecEqual(row0, { 1,2,3 }));
    assert(vecEqual(row1, { 4,5,6 }));

    // operator()
    assert(m(0, 0) == 1);
    assert(m(1, 2) == 6);

    // Modification über operator()
    m(0, 1) = 10;
    assert(m(0, 1) == 10);

    std::cout << "testConstructorAndGetRow passed\n";
}

void testAddRow() {
    Mat m(2, 2, 0.f);
    FloatVec newRow = { 1.f, 2.f };
    m.addRow(newRow);

    assert(m.getShape().rows == 3);
    assert(m.getRow(2)[0] == 1.f && m.getRow(2)[1] == 2.f);

    std::cout << "testAddRow passed\n";
}

void testAdditionOperators() {
    Mat a(2, 2, FloatVec{1, 2, 3, 4});
    Mat b(2, 2, FloatVec{5, 6, 7, 8});

    // operator+=
    a += b;
    assert(vecEqual(a.getRow(0), { 6,8 }));
    assert(vecEqual(a.getRow(1), { 10,12 }));

    // operator+
    Mat c = a + b;
    assert(vecEqual(c.getRow(0), { 11,14 }));
    assert(vecEqual(c.getRow(1), { 17,20 }));

    std::cout << "testAdditionOperators passed\n";
}

void testMultiplicationOperator() {
    Mat a(2, 3, FloatVec{1, 2, 3, 4, 5, 6});
    Mat b(3, 2, FloatVec{7, 8, 9, 10, 11, 12});

    Mat c = a * b;
    // Result should be:
    // [1*7+2*9+3*11, 1*8+2*10+3*12] = [58,64]
    // [4*7+5*9+6*11, 4*8+5*10+6*12] = [139,154]
    assert(vecEqual(c.getRow(0), { 58,64 }));
    assert(vecEqual(c.getRow(1), { 139,154 }));

    std::cout << "testMultiplicationOperator passed\n";
}


int main()
{
    testConstructorAndGetRow();
    testAddRow();
    testAdditionOperators();
    testMultiplicationOperator();

    std::cout << "Done" << std::endl;
}