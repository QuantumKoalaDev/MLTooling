#pragma once

#include <mlt/math/Vector.hpp>

struct mltVectorF
{
    mlt::math::datastructures::Vector<float> implVec;

    mltVectorF(size_t size) : implVec(size) {}
    mltVectorF(std::span<const float> buff) : implVec(buff) {}
    mltVectorF(mlt::math::datastructures::Vector<float>&& mat) : implVec(mat) {}
};


struct mltVectorD
{
    mlt::math::datastructures::Vector<double> implVec;

    mltVectorD(size_t size) : implVec(size) {}
    mltVectorD(std::span<const double> buff) : implVec(buff) {}
    mltVectorD(mlt::math::datastructures::Vector<double>&& mat) : implVec(mat) {}
};
