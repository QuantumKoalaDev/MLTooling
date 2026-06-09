#pragma once

#include <mlt/internal/compute/core/RefCount.hpp>

#include <cstddef>

namespace mlt::compute::core
{
    constexpr size_t DEFAULT_ALIGNMENT = 64;

    struct Storage : RefCounted
    {
        std::byte* data;
        const size_t size;
        const size_t alignment;

        Storage(const Storage&) = delete;
        Storage& operator=(const Storage&) = delete;
        ~Storage();
        
        static Ref<Storage> alloc(const size_t bytes, const size_t alignment = DEFAULT_ALIGNMENT);
        
        private:
        Storage(std::byte* data, size_t size, size_t alignment = DEFAULT_ALIGNMENT);
    };
}

