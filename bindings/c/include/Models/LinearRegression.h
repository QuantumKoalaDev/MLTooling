#ifndef MLTOOLING_CAPI_LINEARREGRESSION_H
#define MLTOOLING_CAPI_LINEARREGRESSION_H

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

#include "Container/Mat.h"

	typedef struct LinearRegressionModel LinearRegressionModel;

	MLTOOLING_CAPI  LinearRegressionModel* lr_create();
	MLTOOLING_CAPI  void lr_destroy(LinearRegressionModel* model);

	MLTOOLING_CAPI void lr_fit(LinearRegressionModel* model, Mat* mat, float* yData, unsigned int yDataLength, float learningRate, unsigned int epochs);
	MLTOOLING_CAPI float lr_predict(LinearRegressionModel* model, float* xFeatures, unsigned int xFeatureLength);

#ifdef __cplusplus
}
#endif

#endif // !MLTOOLING_CAPI_LINEARREGRESSION_H