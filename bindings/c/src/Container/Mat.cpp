#include "Container/Mat.h"
#include "Container/Mat.hpp"

#ifdef __cplusplus
extern "C" {
#endif

struct Mat {
	Container::Mat impl;
};

MLTOOLING_CAPI Mat* ct_mat_create_from_flat_array(
	const float* data,
	const unsigned long rows,
	const unsigned long cols
) {
	Mat* mat = new Mat(
		Container::Mat
		{ 
			static_cast<size_t>(rows),
			static_cast<size_t>(cols),
			std::vector<float>(data, data + rows * cols) 
		}
	);
	return mat;
}

MLTOOLING_CAPI void ct_mat_destroy(Mat* mat) {
	delete mat;
}

MLTOOLING_CAPI unsigned long ct_mat_get_shape_rows(Mat* mat) {
	return mat->impl.getShape().rows;
}

MLTOOLING_CAPI unsigned long ct_mat_get_shape_cols(Mat* mat) {
	return mat->impl.getShape().cols;
}

MLTOOLING_CAPI void ct_mat_copy_row(Mat* mat, const unsigned long rowIndex, float* outArray) {
	std::vector<float> row = mat->impl.getRow(static_cast<size_t>(rowIndex));

	for (size_t i = 0; i < row.size(); i++) {
		outArray[i] = row[i];
	}
}

MLTOOLING_CAPI void ct_mat_add_row(Mat* mat, float* data, unsigned long length) {
	std::vector<float> row(data, data + length);
	mat->impl.addRow(row);
}

MLTOOLING_CAPI float ct_mat_get_item(Mat* mat, const unsigned long row, const unsigned long col) {
	return mat->impl(row, col);
}

MLTOOLING_CAPI void ct_mat_set_item(Mat* mat, const unsigned long row, const unsigned long col, const float value) {
	mat->impl(row, col) = value;
}

#ifdef __cplusplus
}
#endif