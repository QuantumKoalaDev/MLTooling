#include "../../../testdef.hpp"

#include <mlt/internal/compute/backend/cpu/native.hpp>
#include <print>

using namespace mlt::compute::backend::cpu;

static void NativeMatmulTest()
{
    const float a[] = { 3, 2, 1, 1, 0, 2 };
    const float b[] = { 1, 2, 0, 1, 4, 0 };
    float c[] = {0, 0, 0, 0 };

    matmul(a, b, c, 2, 3, 2);

    for (size_t i = 0; i < 4; ++i)
        std::println("{}", c[i]);

    std::println("Tiled:");

    float d[] = {0, 0, 0, 0};
    matmulTiled(a, b, d, 2, 3, 2);

    for (size_t i = 0; i < 4; ++i)
        std::println("{}", d[i]);
}


#include <chrono>
#include <vector>

static void NativeMatmulBenchmark()
{
    constexpr size_t M = 512;
    constexpr size_t K = 512;
    constexpr size_t N = 512;

    std::vector<float> a(M * K, 1);
    std::vector<float> b(K * N, 1);
    std::vector<float> c(M * N, 0);
    std::vector<float> d(M * N, 0);

    constexpr size_t warmupRuns = 3;
    constexpr size_t benchmarkRuns = 10;

    // Warmup
    for (size_t i = 0; i < warmupRuns; ++i)
    {
        matmul(a.data(), b.data(), c.data(), M, K, N);
        matmulTiled(a.data(), b.data(), d.data(), M, K, N);
    }

    auto measure = [](auto&& fn, size_t runs)
    {
        auto start = std::chrono::steady_clock::now();

        for (size_t i = 0; i < runs; ++i)
            fn();

        auto end = std::chrono::steady_clock::now();

        return std::chrono::duration<double, std::milli>(end - start).count();
    };

    const double naiveMs = measure(
        [&]()
        {
            matmul(a.data(), b.data(), c.data(), M, K, N);
        },
        benchmarkRuns
    );

    const double tiledMs = measure(
        [&]()
        {
            matmulTiled(a.data(), b.data(), d.data(), M, K, N);
        },
        benchmarkRuns
    );

    // Anti-Optimization
    volatile int checksum = 0;

    for (size_t i = 0; i < M * N; ++i)
    {
        checksum += c[i];
        checksum += d[i];
    }

    std::println("Matrix: {}x{} * {}x{}", M, K, K, N);
    std::println("Runs: {}", benchmarkRuns);

    std::println(
        "Naive : {:.3f} ms/run",
        naiveMs / benchmarkRuns
    );

    std::println(
        "Tiled : {:.3f} ms/run",
        tiledMs / benchmarkRuns
    );

    std::println(
        "Speedup: {:.2f}x",
        naiveMs / tiledMs
    );

    int valueChecksum = checksum;
    std::println("Checksum: {}", valueChecksum);
}

REGISTER_TEST(NativeMatmulTest)
REGISTER_TEST(NativeMatmulBenchmark)
