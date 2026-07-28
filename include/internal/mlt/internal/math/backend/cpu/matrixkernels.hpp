#pragma once

#include <cstdlib>

namespace mlt::math::backend::cpu
{
    // Example naming für avx:
    // void eltwise_add_f32_avx2();

    
    void eltwise_add_f32_scalar(
        const float* a, 
    );
    void eltwiseAddScalarF32();



    void matAddSimpleF(const float* a, const float* b, size_t incx, size_t incy, float* c);
    void matAddToSimpleF(float* a, const float* b, size_t incx, size_t incy);

    void matAddSimpleD(const double* a, const double* b, size_t incx, size_t incy, double* c);
    void matAddToSimpleD(double* a, const double* b, size_t incx, size_t incy);

    void matSubSimpleF(const float* a, const float* b, size_t incx, size_t incy, float* c);
    void matSubToSimpleF(float *a, const float *b, size_t incx, size_t incy);

    void matSubSimpleD(const double* a, const double* b, size_t incx, size_t incy, double* c);
    void matSubToSimpleD(double* a, const double* b, size_t incx, size_t incy);

    void matMulSimpleF(const float* a, const float* b, size_t incx, size_t incy, float* c);
    void matMulToSimpleF(float* a, const float* b, size_t incx, size_t incy);

    void matMulSimpleD(const double *a, const double *b, size_t incx, size_t incy, double *c);
    void matMulToSimpleD(double* a, const double *b, size_t incx, size_t incy);

    void matAddF(const float* a, const float* b, float* c);
    void matAddToF(float* a, const float* b);




// eltwise_add_f32(
//    const float* a, const size_t* sa,
//    const float* b, const size_t* sb,
//    float* c, const size_t* sc,
//    size_t n);

// gemm_f32(
//    const float* A, size_t sa0, size_t sa1,
//    const float* B, size_t sb0, size_t sb1,
//    float* C, size_t sc0, size_t sc1,
//    size_t M, size_t N, size_t K)
}
