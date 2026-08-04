#pragma once

#include <utility>
#include <expected>

#define MLT_MOVE_VALUE(var) std::move((var)).value()

#define MLT_RETURN_IF_ERROR(exp)    \
    do {                            \
        auto&& mlt_tmp_result = (exp); \
        if (!mlt_tmp_result)           \
            return std::unexpected(mlt_tmp_result.error());    \
    } while (false)


#define MLT_TRY(name, exp)              \
    auto mlt_tmp_result_##name = (exp);    \
    if (!mlt_tmp_result_##name)            \
        return std::unexpected(mlt_tmp_result_##name.error()); \
    auto name = std::move(mlt_tmp_result_##name).value()
