#pragma once

#include "DataColumn.hpp"
#include "IDataColumn.hpp"
#include "core/Shape.hpp"
#include "dataUtils.hpp"

#include <string>
#include <unordered_map>
#include <vector>

namespace mlt::data
{
    class DataFrame
    {
        core::Shape m_shape;
        std::unordered_map<std::string, size_t> m_labelMap;
        std::vector<std::unique_ptr<IDataColumn>> m_data;

      public:
        DataFrame() = default;
        ~DataFrame() = default;

        core::Shape getShape() const;

        void append(const std::string& name, std::unique_ptr<IDataColumn> column);

        template <typename T> DataColumn<T>* get(const std::string& name)
        {
            const size_t position = m_labelMap.at(name);

            if (const IDataColumn* column = m_data[position].get(); DTypeOf<T>::value != column->getType())
                throw std::runtime_error("DataFrame::get(): column type mismatch");

            DataColumn<T>* result = dynamic_cast<DataColumn<T>*>(m_data[position].get());

            if (result == nullptr)
                throw std::bad_cast();

            return result;
        }

        void drop(const std::string& name);
    };
} // namespace mlt::data
