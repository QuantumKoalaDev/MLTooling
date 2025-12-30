#include <vector>
#include <functional>
#include <string>
#include <string_view>
#include <iostream>
#include <format>

class TestRunner
{
	std::vector<std::pair<std::string, std::function<void()>>> m_testList;

public:
	TestRunner() = default;

	static TestRunner& instance()
	{
		static TestRunner runner;
		return runner;
	}

	void registerTest(std::string_view funcName, std::function<void()> func)
	{
		m_testList.emplace_back(funcName, func);
	}

	void runAll()
	{
		unsigned int passed = 0;
		unsigned int failed = 0;

		for (auto& [name, func] : m_testList)
		{
			try
			{
				func();
				passed++;
			}
			catch (const std::exception& e)
			{
				std::cerr << "[FAIL] " << name << ": " << e.what() << std::endl;
				failed++;
			}
		}

		std::cout << std::format("Tests passed: {}, Tests failed: {}", passed, failed) << std::endl;
	}
};