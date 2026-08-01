module;

#include <array>
#include <cstddef>
#include <cstdio>
#include <string_view>

export module mlt.core.error;
export namespace mlt::core 
{
    enum class MltErrorType
    {
        OutOfMemory,
        InvalidAlignment,
        OutOfBounds
    };

    constexpr std::string_view errorTemplate(MltErrorType type)
    {
        switch(type)
        {
            case MltErrorType::OutOfMemory:             return "Out of Memory.";
            case MltErrorType::InvalidAlignment:        return "Invalid alignment: {}";
            case MltErrorType::OutOfBounds:             return "Ouf of bounds: {}";
        }
    }

    struct MltError
    {
        static constexpr size_t MAX_MSG_LEN = 50;
        
        MltErrorType type;
        std::array<char, MAX_MSG_LEN + 1> msg{};

        static MltError make(MltErrorType type, std::string_view detail = {}) noexcept
        {
            MltError err{type, {}};
            std::string_view tmpl = errorTemplate(type);
            
            int written;
            if (detail.empty())
                written = std::snprintf(err.msg.data(), err.msg.size(), "%.*s",
                            (int)tmpl.size(), tmpl.data());
            else
                written = std::snprintf(err.msg.data(), err.msg.size(), "%.*s: %.*s",
                            (int)tmpl.size(), tmpl.data(),
                            (int)detail.size(), detail.data());
            (void)written;
            return err;
        }
    };


}
