#include "Container/Mat.h"
#include "Container/Mat.hpp"

#ifdef __cplusplus
extern "C" {
#endif

struct Mat {
	Container::Mat impl;
};

MLTOOLING_CAPI Mat* ct_mat_create() { return new Mat(); }

MLTOOLING_CAPI Mat* ct_mat_create_from_flat_array(float* data, unsigned long rows, unsigned long cols) {
	Mat* mat = new Mat();
	
	for (unsigned long i = 0; i < rows; ++i) {
		std::vector<float> row(data + i * cols, data + (i + 1) * cols);
		mat->impl.addRow(row);
	}

	return mat;
}

MLTOOLING_CAPI void ct_mat_destroy(Mat* mat) {
	delete mat;
}

MLTOOLING_CAPI void ct_mat_copy_row(Mat* mat, unsigned long rowIndex, float* outArray) {
	std::vector<float> row = mat->impl.getRow(static_cast<size_t>(rowIndex));

	for (size_t i = 0; i < row.size(); i++) {
		outArray[i] = row[i];
	}
}

MLTOOLING_CAPI Shape* ct_mat_get_shape(Mat* mat) {
	Shape* shape = ct_shape_create(static_cast<unsigned long>(mat->impl.getShape().rows), static_cast<unsigned long>(mat->impl.getShape().cols));
	return shape;
}

MLTOOLING_CAPI void ct_mat_add_row(Mat* mat, float* data, unsigned long length) {
	std::vector<float> row(data, data + length);
	mat->impl.addRow(row);
}

#ifdef __cplusplus
}
#endif