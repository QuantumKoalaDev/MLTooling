#include "../testdef.hpp"

#include <mlt/Data.hpp>

#include <vector>

using namespace mlt::core;
using namespace mlt::data;

static void testDataColumnOutOfRange()
{
    DataColumn<int64_t> col({1, 2, 3});

    try
    {
        col[5];
        throw AssertionFailed("Expected std::out_of_range");
    }
    catch (const std::out_of_range&)
    {
    }
}

template <typename T> struct ColumnTraits;

template <> struct ColumnTraits<int64_t>
{
    static constexpr DType dtype = DType::INT64;
    static int64_t zero() { return 0; }
    static int64_t test() { return 5; }
    static std::vector<int64_t> testVec() { return {-1, -3, 5}; }
};

template <> struct ColumnTraits<float>
{
    static constexpr DType dtype = DType::FLOAT32;
    static float zero() { return 0.f; }
    static float test() { return 5.54f; }
    static std::vector<float> testVec() { return {-1.12f, -3.7777f, 5.98745f}; }
};

template <> struct ColumnTraits<double>
{
    static constexpr DType dtype = DType::FLOAT64;
    static double zero() { return 0.0; }
    static double test() { return 5.54; }
    static std::vector<double> testVec() { return {-1.12, -3.7777, 5.98745}; }
};

template <> struct ColumnTraits<std::string>
{
    static constexpr DType dtype = DType::STRING;
    static std::string zero() { return ""; }
    static std::string test() { return "Hello"; }
    static std::vector<std::string> testVec() { return {"world", "!", "olleH"}; }
};

template <> struct ColumnTraits<DateTime>
{
    static constexpr DType dtype = DType::DATETIME;
    static DateTime zero() { return DateTime{}; }
    static DateTime test()
    {
        std::chrono::sys_days day{std::chrono::year{2025} / 12 / 1};
        return std::chrono::time_point_cast<std::chrono::nanoseconds>(day);
    }
    static std::vector<DateTime> testVec()
    {
        std::chrono::sys_days day1{std::chrono::year{2025} / 12 / 1};
        std::chrono::sys_days day2{std::chrono::year{2025} / 12 / 2};
        std::chrono::sys_days day3{std::chrono::year{2024} / 11 / 3};

        return {
            std::chrono::time_point_cast<std::chrono::nanoseconds>(day1),
            std::chrono::time_point_cast<std::chrono::nanoseconds>(day2),
            std::chrono::time_point_cast<std::chrono::nanoseconds>(day3)
        };
    }
};

template <typename T> void testDataColumnConstructorAndAccess()
{
    DataColumn<T> col(3);
    assertEq(col.getSize(), static_cast<size_t>(3), "Wrong size");
    assertEq(static_cast<int>(col.getType()), static_cast<int>(ColumnTraits<T>::dtype), "Wrong dtype");

    for (size_t i = 0; i < 3; ++i)
        assertEq(col[i], ColumnTraits<T>::zero(), "Wrong default value");

    std::vector<T> data = {ColumnTraits<T>::zero(), ColumnTraits<T>::zero(), ColumnTraits<T>::zero()};

    DataColumn<T> col2(data);
    assertEq(col2.getSize(), data.size(), "Wrong size");

    for (size_t i = 0; i < data.size(); ++i)
        assertEq(col2[i], data[i], "Wrong value");

    std::vector<T> colData(3);
    std::vector<bool> mak = {true, false, false};
    DataColumn<T> col3(colData, mak);
    assertEq(col3.getSize(), colData.size(), "Wrong size");
    assertEq(col3[0], colData[0], "Wrong value");
    assertEq(col3.get(1).has_value(), false, "Value should be missing.");
}

template <> void testDataColumnConstructorAndAccess<DateTime>()
{
    DataColumn<DateTime> col(3);
    assertEq(col.getSize(), static_cast<size_t>(3), "Wrong size");
    assertEq(static_cast<int>(col.getType()), static_cast<int>(ColumnTraits<DateTime>::dtype), "Wrong dtype");

    DateTime zero = ColumnTraits<DateTime>::zero();
    const std::string zeroStr = std::format("{:%F %T}", zero);

    for (size_t i = 0; i < 3; ++i)
        assertEq(std::format("{:%F %T}", col[i]), zeroStr, "Wrong default value");

    std::vector<DateTime> data;
    data.push_back(zero);
    data.push_back(zero);
    data.push_back(zero);

    DataColumn<DateTime> col2(data);
    assertEq(col2.getSize(), data.size(), "Wrong size");

    for (size_t i = 0; i < data.size(); ++i)
        assertEq(std::format("{:%F %T}", col2[i]), std::format("{:%F %T}", data[i]), "Wrong value");
}

static void testDataColumnConstructAccessWrapper()
{
    testDataColumnConstructorAndAccess<int64_t>();
    testDataColumnConstructorAndAccess<float>();
    testDataColumnConstructorAndAccess<double>();
    testDataColumnConstructorAndAccess<std::string>();
    testDataColumnConstructorAndAccess<DateTime>();
}

template <typename T> void testDataColumnSetValues()
{
    DataColumn<T> col(3);
    std::vector<T> colData = ColumnTraits<T>::testVec();

    for (size_t i = 0; i < col.getSize(); ++i)
        col[i] = colData[i];

    for (size_t i = 0; i < col.getSize(); ++i)
        assertEq(col[i], colData[i], "Wrong value");
}

template <> void testDataColumnSetValues<DateTime>()
{
    DataColumn<DateTime> col(3);
    std::vector<DateTime> colData = ColumnTraits<DateTime>::testVec();

    for (size_t i = 0; i < col.getSize(); ++i)
        col[i] = colData[i];

    for (size_t i = 0; i < col.getSize(); ++i)
        assertEq(std::format("{:%F %T}", col[i]), std::format("{:%F %T}", colData[i]), "Wrong value");
}

static void testDataColumnSetValuesWrapper()
{
    testDataColumnSetValues<int64_t>();
    testDataColumnSetValues<float>();
    testDataColumnSetValues<double>();
    testDataColumnSetValues<std::string>();
    testDataColumnSetValues<DateTime>();
}

template <typename T> void testDataColumnAppendValues()
{
    DataColumn<T> col(3);
    T testVal = ColumnTraits<T>::test();

    col.append(testVal);
    assertEq(col[3], testVal, "Wrong Value");

    DataColumn<T> col2(0);
    std::vector<T> appendData = ColumnTraits<T>::testVec();
    col2.append(appendData);

    for (size_t i = 0; i < col2.getSize(); ++i)
        assertEq(col2[i], appendData[i], "Wrong value");

    DataColumn<T> col3(appendData);
    DataColumn<T> col4(appendData);
    col3.append(std::move(col4));
    size_t a = appendData.size();

    for (size_t i = 0; i < a; ++i)
        assertEq(col3[i], appendData[i], "Wrong Value");

    for (size_t i = a; i < col3.getSize(); ++i)
        assertEq(col3[i], appendData[i - a], "Wrong Value");
}

template <> void testDataColumnAppendValues<DateTime>()
{
    DataColumn<DateTime> col(3);
    DateTime testVal = ColumnTraits<DateTime>::test();
    col.append(testVal);

    assertEq(std::format("{:%F %T}", col[3]), std::format("{:%F %T}", testVal), "Wrong value");

    DataColumn<DateTime> col2(0);
    std::vector<DateTime> appendData = ColumnTraits<DateTime>::testVec();
    col2.append(appendData);

    for (size_t i = 0; i < col2.getSize(); ++i)
        assertEq(std::format("{:%F %T}", col2[i]), std::format("{:%F %T}", appendData[i]), "Wrong value");

    DataColumn<DateTime> col3(appendData);
    DataColumn<DateTime> col4(appendData);
    col3.append(std::move(col4));
    const size_t a = appendData.size();

    for (size_t i = 0; i < a; ++i)
        assertEq(std::format("{:%F %T}", col3[i]), std::format("{:%F %T}", appendData[i]), "Wrong value");

    for (size_t i = a; i < col3.getSize(); ++i)
        assertEq(std::format("{:%F %T}", col3[i]), std::format("{:%F %T}", appendData[i - a]), "Wrong value");
}

static void testDataColumnAppendValuesWrapper()
{
    testDataColumnAppendValues<int64_t>();
    testDataColumnAppendValues<float>();
    testDataColumnAppendValues<double>();
    testDataColumnAppendValues<std::string>();
    testDataColumnAppendValues<DateTime>();
}

static void testDataFrameConstructorAndAccess()
{
    DataFrame frame{};

    DataColumn<int64_t> col(100);
    frame.append("test", std::make_unique<DataColumn<int64_t>>(col));
    const DataColumn<int64_t>* testCol = frame.get<int64_t>("test");

    for (size_t i = 0; i < testCol->getSize(); ++i)
        assertEq(col[i], static_cast<int64_t>(0), "Wrong value");
}

REGISTER_TEST(testDataColumnConstructAccessWrapper);
REGISTER_TEST(testDataColumnOutOfRange);
REGISTER_TEST(testDataColumnSetValuesWrapper);
REGISTER_TEST(testDataColumnAppendValuesWrapper);
REGISTER_TEST(testDataFrameConstructorAndAccess);
