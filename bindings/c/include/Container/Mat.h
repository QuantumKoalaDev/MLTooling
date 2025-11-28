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
#include "Container/Shape.h"
	
	typedef struct Mat;

	MLTOOLING_CAPI Mat* ct_mat_create();
	MLTOOLING_CAPI Mat* ct_mat_create_from_flat_array(float* data, unsigned long rows, unsigned long cols);
	MLTOOLING_CAPI void ct_mat_destroy(Mat* mat);

	MLTOOLING_CAPI void ct_mat_copy_row(Mat* mat, unsigned long rowIndex, float* outArray);
	MLTOOLING_CAPI Shape* ct_mat_get_shape(Mat* mat);
	MLTOOLING_CAPI void  ct_mat_add_row(Mat* mat, float* data, unsigned long cols);

#ifdef __cplusplus
}
#endif

#endif // !MLTOOLING_CAPI_MAT_H
