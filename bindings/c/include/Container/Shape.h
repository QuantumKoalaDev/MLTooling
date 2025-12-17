#ifndef MLTOOLING_CAPI_SHAPE_H
#define MLTOOLING_CAPI_SHAPE_H

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
	
	typedef struct Shape;

//-------------------------------------------------------------------------
//		Python Bindings (can also be used in C but might not be optimal)
//		Depricated for Python. Got replaced by a dataclass
//-------------------------------------------------------------------------

	MLTOOLING_CAPI Shape* ct_shape_create(unsigned long rows, unsigned long cols);
	MLTOOLING_CAPI void ct_shape_destroy(Shape* shape);
	MLTOOLING_CAPI unsigned long ct_shape_getRows(Shape* shape);
	MLTOOLING_CAPI unsigned long ct_shape_getCols(Shape* shape);
	
#ifdef __cplusplus
}
#endif


#endif // !MLTOOLING_CAPI_SHAPE_H
