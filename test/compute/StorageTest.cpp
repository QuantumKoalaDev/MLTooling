#include "../testdef.hpp"
#include <mlt/internal/compute/core/Storage.hpp>

#define MLT_STORAGE_DEFAULT float

using namespace mlt::compute::core;

static constexpr size_t testSize = 10;

static void testConstructorStorage()
{
    Ref<Storage> s = Storage::alloc(testSize);

    assertEq(s->size, testSize, "Storage constructor allocated wrong amount of bytes.");
}

REGISTER_TEST(testConstructorStorage);
