module;

#include <mlt/internal/compute/core/RefCount.hpp>
#include <cstddef>
#include <expected>

export module mlt.internal.core.storage;

import mlt.core.error;

export namespace mlt::compute::core 
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

        static std::expected<Ref<Storage>, mlt::core::MltError> alloc(const size_t bytes, const size_t alignment = DEFAULT_ALIGNMENT);
    };
}
