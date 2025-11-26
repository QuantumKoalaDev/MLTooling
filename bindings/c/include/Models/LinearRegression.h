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

	typedef struct LinearRegressionModel LinearRegressionModel;

	MLTOOLING_CAPI  LinearRegressionModel* lr_create();
	MLTOOLING_CAPI  void lr_destroy(LinearRegressionModel* model);

#ifdef __cplusplus
}
#endif
