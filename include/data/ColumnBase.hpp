#include <string>

namespace mlt::data
{
	class ColumnBase
	{
	public:
		virtual const std::string& getName() const = 0;
		virtual size_t getSize() const = 0;
		virtual ~ColumnBase() = default;
	};
}