#pragma once

#include "ColumnBase.hpp"
#include "DataColumn.hpp"
#include "../core/Shape.hpp"

#include <vector>
#include <unordered_map>
#include <memory>

namespace mlt::data
{
	class DataFrame
	{
		core::Shape m_shape;
		std::vector<std::unique_ptr<ColumnBase>> m_data;
		// Not ideal, names are stored twice. Here and inside DataColumn.
		std::unordered_map<std::string, size_t> m_indexMap;
	public:
		template <typename T>
		explicit DataFrame(DataColumn<T> col) : 
			m_shape(1,1),
			m_indexMap { {col.getName(), 0}}
		{
			std::unique_ptr<ColumnBase> colPtr = std::make_unique<DataColumn<T>>(std::move(col));
			m_data.push_back(std::move(colPtr));
		}

		~DataFrame() = default;

		const ColumnBase& operator[](const std::string& colName);

		core::Shape getShape() const;

		template <typename T>
		const DataColumn<T>& getColumn(const std::string& colName) const
		{
			size_t colIndex = m_indexMap.at(colName);
			return dynamic_cast<const DataColumn<T>&>(*m_data[colIndex]);
		}

		template <typename T>
		void appendCol(DataColumn<T> col)
		{
			size_t nextIndex = m_data.size();
			m_indexMap[col.getName()] = nextIndex;

			std::unique_ptr<ColumnBase> colPtr = std::make_unique<DataColumn<T>>(std::move(col));
			m_data.push_back(std::move(colPtr));
			m_shape.cols++;
		}

		void appendCol(std::unique_ptr<ColumnBase> col);
	};
}