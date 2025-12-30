#pragma once

#include "core/Shape.hpp"
#include "dataUtils.hpp"
#include "IDataColumn.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace mlt::data
{
	class DataFrame
	{
		core::Shape m_shape;
		std::unordered_map<std::string, size_t> m_indices;
		std::vector<ColumnEntry> m_entries;
		std::vector<IDataColumn> m_data;

	public:
		DataFrame() = default;
		~DataFrame() = default;

		DataFrame Clone();
		bool isEqual(DataFrame& other) const;


		core::Shape getShape();
	};

	struct ColumnHandle
	{
		std::string name;
		DataFrame* dataFrame;
	};
}


// struct ColumnEntry => name, DataType, Index
// map fuer indexing => name: string, index: size_t
// data => vector<IColumn> (Columns koennen nur int, long, float, double, datetime, string, (object)
// struct ColumnHandle => DataFrame*, std::string colName, dataType

// class Column => ptr auf IColumn, Dtype, name, 


//auto* base = m_data[colIndex].get();
//assert(base->kind() == ColumnKindOf<T>);
//return static_cast<const DataColumn<T>&>(*base);
