module;

#include <string>

export module mlt.core.error;
export namespace mlt::core 
{
    enum class MltErrorType
    {
        OutOfMemory,
        InvalidArgument
    };

    struct MltError
    {
        MltErrorType type;
        std::string msg;
    };
}
