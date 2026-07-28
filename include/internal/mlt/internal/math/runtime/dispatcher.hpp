#include <cstddef>
#include <memory>
#include <vector>


enum class DType
{
    FLOAT32,
    FLOAT64
};

struct MltArrayF
{
    float* data;
    size_t len;
};

struct MltArrayD
{
    double* data;
    size_t len;
};

struct Tensor
{
    void* data;
    DType type;
};

struct TensorView
{
    std::shared_ptr<void> array;
    std::vector<size_t> shape;
    std::vector<size_t> strides;
    DType type;
};


namespace mlt::math::runtime
{
    class Dispatcher
    {
        public:
    };
}
