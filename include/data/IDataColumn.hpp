#pragma once

#include "dataUtils.hpp"

namespace mlt::data
{

	/// @class IDataColumn
	/// @brief Base class for all DataFrame columns.
	/// 
	/// IDataColumn enables heterogeneous data in a DataFrame via polymorphism.
	class IDataColumn
	{
	public:
		virtual ~IDataColumn() = default;
		virtual DType getType() const noexcept = 0;
		virtual size_t getSize() const noexcept = 0;
	};
}
