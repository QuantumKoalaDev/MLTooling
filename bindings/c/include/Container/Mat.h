#ifndef MLTOOLING_CAPI_MAT_H
#define MLTOOLING_CAPI_MAT_H

#ifdef _WIN32
	#ifdef MLTOOLING_CAPI_EXPORTS
		#define MLTOOLING_CAPI __declspec(dllexport)
	#else
		#define MLTOOLING_CAPI __declspec(dllimport)
	#endif
#else
	#define MLTOOLING_CAPI
#endif

#ifdef __cplusplus
extern "C" {
#endif
	
	typedef struct Mat Mat;

	typedef enum {
		MLT_OK = 0,
		MLT_ERR_NULL_PTR,
		MLT_ALLOCATION_FAILED,
		MLT_ERR_OUT_OF_RANGE,
		MLT_INVALID_ARGUMENT,
		MLT_ERR_INTERNAL
		
	} mlt_status;

//-------------------------------------------------------------------------
//		Python Bindings (can also be used in C but might not be optimal
//-------------------------------------------------------------------------
	MLTOOLING_CAPI mlt_status mlt_ct_mat_create_with_val(unsigned long rows, unsigned long cols, float init, Mat** out_mat);
	MLTOOLING_CAPI mlt_status mlt_ct_mat_create_from_flat_array(unsigned long rows, unsigned long cols, const float* data, Mat** out_mat);

	MLTOOLING_CAPI mlt_status mlt_ct_mat_destroy(Mat* mat);

	MLTOOLING_CAPI mlt_status mlt_ct_mat_get_shape_rows(const Mat* mat, unsigned long* out);
	MLTOOLING_CAPI mlt_status mlt_ct_mat_get_shape_cols(const Mat* mat, unsigned long* out);

	MLTOOLING_CAPI mlt_status mlt_ct_mat_copy_row(unsigned long rowIndex, const Mat* mat, float* outArray);
	MLTOOLING_CAPI mlt_status mlt_ct_mat_append_row(unsigned long length, const float* data, Mat* mat);

	MLTOOLING_CAPI mlt_status mlt_ct_mat_get_item(unsigned long row, unsigned long col, const Mat* mat, float* out);
	MLTOOLING_CAPI mlt_status mlt_ct_mat_set_item(unsigned long row, unsigned long col, const float value, Mat* mat);

	MLTOOLING_CAPI mlt_status mlt_ct_mat_add(const Mat* mat, const Mat* other, Mat** out);
	MLTOOLING_CAPI mlt_status mlt_ct_mat_add_in_place(Mat* mat, const Mat* other);

	MLTOOLING_CAPI mlt_status mlt_ct_mat_mul(const Mat* mat, const Mat* other, Mat** out);

#ifdef __cplusplus
}
#endif

#endif // !MLTOOLING_CAPI_MAT_H
