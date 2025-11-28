#include "Models/LinearRegression.h"
#include "Models/LinearRegressionModel.hpp"

#include "Container/Mat.h"
#include "Container/Mat.hpp"

struct Mat {
	Container::Mat impl;
};

struct LinearRegressionModel {
	Models::LinearRegressionModel impl;
};


MLTOOLING_CAPI LinearRegressionModel* lr_create() { return new LinearRegressionModel(); }
MLTOOLING_CAPI void lr_destroy(LinearRegressionModel* m) { delete m; }

MLTOOLING_CAPI void lr_fit(LinearRegressionModel* model, Mat* mat, float* yData, unsigned int yDataLength, float learningRate, unsigned int epochs) {
	std::vector<float> y(yData, yData + yDataLength);
	model->impl.fit(mat->impl, y, learningRate, epochs);
}

MLTOOLING_CAPI float lr_predict(LinearRegressionModel* model, float* xFeatures, unsigned int xFeatureLength) {
	std::vector<float> x(xFeatures, xFeatures + xFeatureLength);
	return model->impl.predict(x);
}