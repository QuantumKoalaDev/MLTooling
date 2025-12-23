#include <string>
#include <typeindex>
#include <cstddef>

namespace mlt::data
{
	class ColumnBase
	{
		std::type_index m_type;
	public:
		ColumnBase(std::type_index type) : m_type(type) {}
		virtual std::type_index getType() const { return m_type; }
		virtual const std::string& getName() const = 0;
		virtual size_t getSize() const = 0;
		virtual ~ColumnBase() = default;
	};
}