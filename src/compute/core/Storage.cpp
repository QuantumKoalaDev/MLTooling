#include <cstddef>
#include <mlt/internal/compute/core/Storage.hpp>

#include <new>

using namespace mlt::compute::core;

Storage::Storage(std::byte* data, size_t size, size_t alignment)
    : data(data), size(size), alignment(alignment)
{}


Storage::~Storage()
{
   ::operator delete(data, std::align_val_t(alignment)); 
}

Ref<Storage> Storage::alloc(const size_t bytes, const size_t alignment)
{
    std::byte* data = static_cast<std::byte*>(
        ::operator new(bytes, std::align_val_t(alignment))
    );

    return Ref<Storage>(new Storage(data, bytes, alignment));
}
