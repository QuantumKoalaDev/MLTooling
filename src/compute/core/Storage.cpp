#include <mlt/internal/compute/core/Storage.hpp>

#include <array>
#include <charconv>
#include <new>
#include <string_view>


using namespace mlt::compute::core;

Storage::Storage(std::byte* data, size_t size, size_t alignment)
    : data(data), size(size), alignment(alignment)
{}


Storage::~Storage()
{
   ::operator delete(data, std::align_val_t(alignment), std::nothrow); 
}

std::expected<Ref<Storage>, mlt::core::MltError> Storage::alloc(const size_t bytes, const size_t alignment)
{
    if (alignment == 0 || (alignment & (alignment-1)) != 0)
    {
        char buff[24];
        std::to_chars_result result = std::to_chars(buff, buff + sizeof(buff), alignment);
        std::string_view detail(buff, result.ptr - buff);   

        return std::unexpected(mlt::core::MltError::make(mlt::core::MltErrorType::InvalidAlignment, detail));
    }

    std::byte* data = static_cast<std::byte*>(
            ::operator new(bytes, std::align_val_t(alignment), std::nothrow)
        );

    if (!data)
        return std::unexpected(mlt::core::MltError::make(mlt::core::MltErrorType::OutOfMemory));

    Storage* storage = new (std::nothrow) Storage(data, bytes, alignment);

    if (!storage)
    {
        ::operator delete(data, std::align_val_t(alignment), std::nothrow);
        return std::unexpected(mlt::core::MltError::make(mlt::core::MltErrorType::OutOfMemory));
    }

    return Ref<Storage>(new Storage(data, bytes, alignment));
}
