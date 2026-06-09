#pragma once

#include <cstdint>

namespace mlt::compute::backend::cpu {
    void matmul_f32(const float* a, const float* b, float* c, int64_t m, int64_t k, int64_t n);
    void add_f32(const float* a, const float* b, float* c, int64_t n);
    void mul_f32(const float* a, const float* b, float* c, int64_t n);
    void sum_f32(const float* a, float* res, int64_t n);
    void sigmoid(const float* a, float* c, int64_t n);
}
