#include "Container/Mat.h"
#include "Container/Mat.hpp"

#include <stdexcept>

#ifdef __cplusplus
extern "C" {
#endif

struct Mat {
	Container::Mat impl;
};

MLTOOLING_CAPI mlt_status mlt_ct_mat_create_with_val(unsigned long rows, unsigned long cols, float init, Mat** out_mat)
{
	if (!out_mat)
		return MLT_ERR_NULL_PTR;

	try 
	{
		*out_mat = new Mat(
			Container::Mat
			{
				static_cast<size_t>(rows),
				static_cast<size_t>(cols),
				init
			}
		);
	}
	catch (const std::bad_alloc&)
	{
		*out_mat = nullptr;
		return MLT_ALLOCATION_FAILED;
	}
	catch (...)
	{
		*out_mat = nullptr;
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_create_from_flat_array(const unsigned long rows, const unsigned long cols, const float* data, Mat** out_mat)
{
	if (!out_mat)
		return MLT_ERR_NULL_PTR;

	try
	{
		*out_mat = new Mat(
			Container::Mat
			{
				static_cast<size_t>(rows),
				static_cast<size_t>(cols),
				std::vector<float>(data, data + rows * cols)
			}
		);
	}
	catch (const std::bad_alloc&)
	{
		*out_mat = nullptr;
		return MLT_ALLOCATION_FAILED;
	}
	catch (...)
	{
		*out_mat = nullptr;
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_destroy(Mat* mat)
{
	if (!mat)
		return MLT_ERR_NULL_PTR;

	try
	{
		delete mat;
	}
	catch (...)
	{
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_get_shape_rows(const Mat* mat, unsigned long* out)
{
	if (!mat || !out)
		return MLT_ERR_NULL_PTR;

	*out = static_cast<unsigned long>(mat->impl.getShape().rows);

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_get_shape_cols(const Mat* mat, unsigned long* out)
{
	if (!mat || !out)
		return MLT_ERR_NULL_PTR;

	*out = static_cast<unsigned long>(mat->impl.getShape().cols);

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_copy_row(const unsigned long rowIndex, const Mat* mat, float* outArray)
{
	if (!mat || !outArray)
		return MLT_ERR_NULL_PTR;

	try
	{
		std::vector<float> row = mat->impl.getRow(static_cast<size_t>(rowIndex));

		for (size_t i = 0; i < row.size(); ++i)
			outArray[i] = row[i];
	}
	catch (std::out_of_range&)
	{
		return MLT_ERR_OUT_OF_RANGE;
	}
	catch (...)
	{
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_append_row(const unsigned long length, const float* data, Mat* mat)
{
	if (!mat || !data)
		return MLT_ERR_NULL_PTR;

	try
	{
		std::vector<float> row(data, data + length);
		mat->impl.addRow(row);
	}
	catch (...)
	{
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;

}

MLTOOLING_CAPI mlt_status mlt_ct_mat_get_item(const unsigned long row, const unsigned long col, const Mat* mat, float* out)
{
	if (!mat || !out)
		return MLT_ERR_NULL_PTR;

	try
	{
		*out = mat->impl(row, col);
	}
	catch (std::out_of_range&)
	{
		return MLT_ERR_OUT_OF_RANGE;
	}
	catch (...)
	{
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_set_item(const unsigned long row, const unsigned long col, const float value, Mat* mat)
{
	if (!mat)
		return MLT_ERR_NULL_PTR;

	try
	{
		mat->impl(row, col) = value;
	}
	catch (std::out_of_range&)
	{
		return MLT_ERR_OUT_OF_RANGE;
	}
	catch (...)
	{
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_add(const Mat* mat, const Mat* other, Mat** out)
{
	if (!mat || !other || !out)
		return MLT_ERR_NULL_PTR;

	try
	{
		Container::Mat addedMat = mat->impl + other->impl;

		*out = new Mat(addedMat);
	}
	catch (std::bad_alloc&)
	{
		return MLT_ALLOCATION_FAILED;
	}
	catch (std::invalid_argument&)
	{
		return MLT_INVALID_ARGUMENT;
	}
	catch (...)
	{
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_add_in_place(Mat* mat, const Mat* other)
{
	if (!mat || !other)
		return MLT_ERR_NULL_PTR;

	try
	{
		mat->impl += other->impl;
	}
	catch (std::invalid_argument&)
	{
		return MLT_INVALID_ARGUMENT;
	}
	catch (...)
	{
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

MLTOOLING_CAPI mlt_status mlt_ct_mat_mul(const Mat* mat, const Mat* other, Mat** out)
{
	if (!mat || !other || !out)
		return MLT_ERR_NULL_PTR;

	try
	{
		Container::Mat matMul = mat->impl * other->impl;
		*out = new Mat(matMul);
	}
	catch (const std::invalid_argument&)
	{
		return MLT_INVALID_ARGUMENT;
	}
	catch (...)
	{
		return MLT_ERR_INTERNAL;
	}

	return MLT_OK;
}

#ifdef __cplusplus
}
#endif