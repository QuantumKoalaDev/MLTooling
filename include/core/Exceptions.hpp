#pragma once

#include <filesystem>
#include <stdexcept>

namespace mlt::core
{
    /// @class NotImplementedException
    /// @brief Exception type to indicate that a function or feature has not been implemented yet.
    ///
    /// Inherits from std::logic_error, so it represents a logic error in the program.
    class NotImplementedException : public std::logic_error
    {
      public:
        /// @brief Default constructor
        ///
        /// Initializes the std::logic_error base class with a default message.
        NotImplementedException() : std::logic_error("Not implemented yet.") {}
    };
} // namespace mlt::core