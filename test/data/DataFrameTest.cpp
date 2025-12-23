#include "../testdef.hpp"

#include <MLTooling.h>

#include <vector>

using namespace mlt::data;

static void testDataColumnConstructorAndBasicAccess()
{
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

REGISTER_TEST(testDataColumnConstructorAndBasicAccess);
REGISTER_TEST(testDataColumnOutOfRange);
REGISTER_TEST(testDataColumnAppendValue);
REGISTER_TEST(testDataColumnReplaceValuesAllTypes);
REGISTER_TEST(testDataColumnGetDataAllTypes);
REGISTER_TEST(testDataColumnToStringAllTypes);
REGISTER_TEST(testDataColumnGetTypeAllTypes);