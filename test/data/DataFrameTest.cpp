#include "../testdef.hpp"

#include <MLTooling.h>

#include <vector>
#include <iostream>

using namespace mlt::core;
using namespace mlt::data;

static void testDataColumnConstructorAndBasicAccess()
{
	DataColumn<int> colIntBasic("ints", 3);
	assertEq(colIntBasic.getName(), std::string("ints"), "int name");
	assertEq(colIntBasic.getSize(), size_t(3), "int size");
	assertEq(colIntBasic(1), 0, "int access");

	DataColumn<float> colFloatBasic("floats", 3);
	assertEq(colFloatBasic.getName(), std::string("floats"), "float name");
	assertEq(colFloatBasic.getSize(), size_t(3), "float size");
	assertEq(colFloatBasic(1), 0.f, "float access");

	DataColumn<std::string> colStringBasic("strings", 3);
	assertEq(colStringBasic.getName(), std::string("strings"), "string name");
	assertEq(colStringBasic.getSize(), size_t(3), "string size");
	assertEq(colStringBasic(1), std::string(""), "string access");

	DataColumn<int> colInt("ints", { 1, 2, 3 });
	assertEq(colInt.getName(), std::string("ints"), "int name");
	assertEq(colInt.getSize(), size_t(3), "int size");
	assertEq(colInt(1), 2, "int access");

	DataColumn<float> colFloat("floats", { 1.0f, 2.5f, 3.0f });
	assertEq(colFloat.getName(), std::string("floats"), "float name");
	assertEq(colFloat.getSize(), size_t(3), "float size");
	assertEq(colFloat(1), 2.5f, "float access");

	DataColumn<std::string> colString("strings", { "a", "b", "c" });
	assertEq(colString.getName(), std::string("strings"), "string name");
	assertEq(colString.getSize(), size_t(3), "string size");
	assertEq(colString(1), std::string("b"), "string access");
}

static void testDataColumnOutOfRange()
{
	DataColumn<int> col("numbers", { 1, 2, 3 });

	try
	{
		(void)col(3);
		throw AssertionFailed("Expected std::out_of_range");
	}
	catch (const std::out_of_range&)
	{
		return;
	}
}

static void testDataColumnAppendValue()
{
	DataColumn<int> colInt("ints", { 1 });
	colInt.appendValue(2);
	assertEq(colInt.getSize(), size_t(2), "int append size");
	assertEq(colInt(1), 2, "int append value");

	DataColumn<float> colFloat("floats", { 1.0f });
	colFloat.appendValue(2.5f);
	assertEq(colFloat.getSize(), size_t(2), "float append size");
	assertEq(colFloat(1), 2.5f, "float append value");

	DataColumn<std::string> colString("strings", { "a" });
	colString.appendValue("b");
	assertEq(colString.getSize(), size_t(2), "string append size");
	assertEq(colString(1), std::string("b"), "string append value");
}

static void testDataColumnReplaceValuesAllTypes()
{
	DataColumn<int> colInt("ints", { 1, 2, 2 });
	colInt.replaceValues(2, 42);
	assertEq(colInt(1), 42, "int replace");

	DataColumn<float> colFloat("floats", { 1.0f, 2.0f, 2.0f });
	colFloat.replaceValues(2.0f, 4.5f);
	assertEq(colFloat(1), 4.5f, "float replace");

	DataColumn<std::string> colString("strings", { "a", "b", "b" });
	colString.replaceValues("b", "x");
	assertEq(colString(1), std::string("x"), "string replace");
}

static void testDataColumnGetDataAllTypes()
{
	DataColumn<int> colInt("ints", { 1, 2 });
	std::span<const int> spanInt = colInt.getData();
	assertEq(spanInt.size(), size_t(2), "int span size");
	assertEq(spanInt[0], 1, "int span value");

	DataColumn<float> colFloat("floats", { 1.0f, 2.0f });
	std::span<const float> spanFloat = colFloat.getData();
	assertEq(spanInt.size(), size_t(2), "float span size");
	assertEq(spanFloat[1], 2.0f, "float span value");

	DataColumn<std::string> colString("strings", { "a", "b" });
	std::span<const std::string> spanString = colString.getData();
	assertEq(spanInt.size(), size_t(2), "string span size");
	assertEq(spanString[1], std::string("b"), "string span value");
}

static void testDataColumnToStringAllTypes()
{
	DataColumn<int> colInt("ints", { 1, 2 });
	assertEq(
		colInt.toString(),
		std::string("ints\n1\n2\n"),
		"int toString"
	);

	DataColumn<float> colFloat("floats", { 1.5f });
	assertEq(
		colFloat.toString(),
		std::string("floats\n1.5\n"),
		"float toString"
	);

	DataColumn<std::string> colString("strings", { "a", "b" });
	assertEq(
		colString.toString(),
		std::string("strings\na\nb\n"),
		"string toString"
	);
}

static void testDataColumnGetTypeAllTypes()
{
	assertEq(
		DataColumn<int>("i", {}).getType(),
		std::type_index(typeid(int)),
		"type int"
	);

	assertEq(
		DataColumn<float>("f", {}).getType(),
		std::type_index(typeid(float)),
		"type float"
	);

	assertEq(
		DataColumn<std::string>("s", {}).getType(),
		std::type_index(typeid(std::string)),
		"type string"
	);
}

static void testDataFrameConstructor()
{
	DataColumn<int> colInt("ints", { 1, 2, 3 });
	DataFrame dfInt(colInt);

	const DataColumn<int>& cInt = dfInt.getColumn<int>("ints");
	assertEq(cInt.getName(), "ints", "Constructor test int - name mismatch");
	assertEq(cInt.getType(), typeid(int), "Constructor test int - type mismatch");
	assertEq(cInt.getSize(), static_cast<size_t>(3), "Constructor test int - size mismatch");
	assertEq(cInt(0), 1, "Constructor test int - value mismatch at index 0");

	DataColumn<float> colFloat("floats", { 1.1f, 2.2f, 3.3f });
	DataFrame dfFloat(colFloat);

	const DataColumn<float>& cFloat = dfFloat.getColumn<float>("floats");
	assertEq(cFloat.getName(), "floats", "Constructor test float - name mismatch");
	assertEq(cFloat.getType(), typeid(float), "Constructor test float - type mismatch");
	assertEq(cFloat.getSize(), static_cast<size_t>(3), "Constructor test float - size mismatch");
	assertEq(cFloat(2), 3.3f, "Constructor test float - value mismatch at index 2");

	DataColumn<std::string> colString("names", { "Alice", "Bob" });
	DataFrame dfString(colString);

	const DataColumn<std::string>& cString = dfString.getColumn<std::string>("names");
	assertEq(cString.getName(), "names", "Constructor test string - name mismatch");
	assertEq(cString.getType(), typeid(std::string), "Constructor test string - type mismatch");
	assertEq(cString.getSize(), static_cast<size_t>(2), "Constructor test string - size mismatch");
	assertEq(cString(1), "Bob", "Constructor test string - value mismatch at index 1");
}

static void testDataFrameAppendCol()
{
	DataFrame dfInt(DataColumn<int>("ints", { 1,2,3 }));
	DataColumn<int> col2Int("more_ints", { 10, 20 });
	dfInt.appendCol(col2Int);

	const DataColumn<int>& cInt = dfInt.getColumn<int>("more_ints");
	assertEq(cInt.getSize(), size_t(2), "appendCol int - size mismatch");
	assertEq(cInt(0), 10, "appendCol int - value mismatch at index 0");

	DataFrame dfFloat(DataColumn<float>("floats", { 1.1f }));
	DataColumn<float> col2Float("more_floats", { 4.4f, 5.5f });
	dfFloat.appendCol(col2Float);

	const DataColumn<float>& cFloat = dfFloat.getColumn<float>("more_floats");
	assertEq(cFloat.getSize(), size_t(2), "appendCol float - size mismatch");
	assertEq(cFloat(1), 5.5f, "appendCol float - value mismatch at index 1");

	DataFrame dfString(DataColumn<std::string>("names", { "Alice" }));
	DataColumn<std::string> col2String("more_names", { "Charlie" });
	dfString.appendCol(col2String);

	const DataColumn<std::string>& cString = dfString.getColumn<std::string>("more_names");
	assertEq(cString.getSize(), size_t(1), "appendCol string - size mismatch");
	assertEq(cString(0), "Charlie", "appendCol string - value mismatch at index 0");
}

static void testDataFrameGetCol()
{
	DataFrame dfInt(DataColumn<int>("ints", { 1,2 }));
	DataFrame dfFloat(DataColumn<float>("floats", { 1.1f,2.2f }));
	DataFrame dfString(DataColumn<std::string>("names", { "Alice","Bob" }));

	const DataColumn<int>& cInt = dfInt.getColumn<int>("ints");
	assertEq(cInt.getSize(), static_cast<size_t>(2), "getColumn int - size mismatch");
	assertEq(cInt(1), 2, "getColumn int - value mismatch");

	const DataColumn<float>& cFloat = dfFloat.getColumn<float>("floats");
	assertEq(cFloat.getSize(), static_cast<size_t>(2), "getColumn float - size mismatch");
	assertEq(cFloat(0), 1.1f, "getColumn float - value mismatch");

	const DataColumn<std::string>& cString = dfString.getColumn<std::string>("names");
	assertEq(cString.getSize(), static_cast<size_t>(2), "getColumn string - size mismatch");
	assertEq(cString(0), "Alice", "getColumn string - value mismatch");
}

REGISTER_TEST(testDataColumnConstructorAndBasicAccess);
REGISTER_TEST(testDataColumnOutOfRange);
REGISTER_TEST(testDataColumnAppendValue);
REGISTER_TEST(testDataColumnReplaceValuesAllTypes);
REGISTER_TEST(testDataColumnGetDataAllTypes);
REGISTER_TEST(testDataColumnToStringAllTypes);
REGISTER_TEST(testDataColumnGetTypeAllTypes);
REGISTER_TEST(testDataFrameConstructor);
REGISTER_TEST(testDataFrameAppendCol);
REGISTER_TEST(testDataFrameGetCol);