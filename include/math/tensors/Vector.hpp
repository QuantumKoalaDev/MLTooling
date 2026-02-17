#pragma once

#include <concepts>
#include <vector>
namespace mlt::math::tensors 
{
    template<typename T>
    concept Numeric = std::integral<T> || std::floating_point<T>;

    template<Numeric T>
    class Vector
    {
        std::vector<T> data;
        
        public:
        Vector() = default;
        ~Vector() = default;

        Vector(size_t n) : data(n) {}
        Vector(std::initializer_list<T> init) : data(init) {}

        size_t getSize() { return data.size(); }
               
    };
}
