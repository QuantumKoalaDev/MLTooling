#pragma once

#include <chrono>
#include <format>
#include <functional>
#include <iostream>
#include <print>
#include <ratio>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

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

    void registerTest(std::string_view funcName, const std::function<void()>& func)
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


class BenchRunner
{
    std::unordered_map<std::string, std::function<void()>> mBenchList;

    void runFunc(const std::string& name)
    {
        constexpr size_t WARMUP_RUNS = 3;
        constexpr size_t BENCH_RUNS = 10;

        const std::function<void()>& func = mBenchList.at(name);
        
        std::println("======================================");
        std::println("Running benchmark: {}", name);
        std::println("Running warm up...");

        for (size_t i = 0; i < WARMUP_RUNS; ++i)
            func();

        std::println("Running benchmark...");

        auto start = std::chrono::steady_clock::now();

        for (size_t i = 0; i < BENCH_RUNS; ++i)
            func();

        auto end = std::chrono::steady_clock::now();
        
        auto time = std::chrono::duration<double, std::milli>(end - start).count() / double(BENCH_RUNS);
        
        std::println("Time: {}", time );
        std::println("======================================");
        std::println("");
    }

    void runAll()
    {
        for (const std::pair<std::string, std::function<void()>>& elem : mBenchList)
        {
            runFunc(elem.first);
        }
    }

    public:
    BenchRunner() = default;

    static BenchRunner& instance()
    {
        static BenchRunner runner;
        return runner;
    }

    void registerBench(std::string_view name, const std::function<void()>& func)
    {
        mBenchList.insert(std::make_pair(name, func));
    }

    void run(const std::string& name)
    {
        if (name.empty())
            runAll();
        else
        {
            bool check = mBenchList.contains(name);

            if(!check)
                throw std::runtime_error(std::format("Benchmark does not exist: {}", name));
            
            runFunc(name);
        }
    }

};

#define REGISTER_BENCH(func)                                                        \
    struct func##_registrar                                                         \
    {                                                                               \
        func##_registrar() { BenchRunner::instance().registerBench(#func, func); }  \
    } func##_instance;                                                              \
