#include "Models/LinearRegression.h"
#include "Models/LinearRegressionModel.h"

struct LinearRegressionModel {
	Models::LinearRegressionModel impl;
};

MLTOOLING_CAPI LinearRegressionModel* lr_create() { return new LinearRegressionModel(); }
MLTOOLING_CAPI void lr_destroy(LinearRegressionModel* m) { delete m; }
