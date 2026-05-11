#include <mlt/models/linearRegression.h>

#include "linearRegressionInternal.hpp"
#include <mlt/math/Exceptions.hpp>

#include "matrixInternal.hpp"
#include "vectorInternal.hpp"

mltStatus mltLinearRegressionCreate(mltLinearRegression** out)
{
    if (!out)
        return MLT_STATUS_ERR_NULL_PTR;

    *out = new mltLinearRegression();

    return MLT_STATUS_SUCCESS;
}

mltStatus mltLinearRegressionDestroy(mltLinearRegression* model)
{
    if (!model)
        return MLT_STATUS_ERR_NULL_PTR;

    delete model;

    return MLT_STATUS_SUCCESS;
}

mltStatus mltLinearRegressionPredict(const mltLinearRegression* model, const mltVectorF* features, float* out)
{
    if (!model || !features || !out)
        return MLT_STATUS_ERR_NULL_PTR;

    try
    {
        *out = model->impl.predict(features->implVec);
    }
    catch (const mlt::math::ShapeMismatchException&)
    {
        return MLT_STATUS_SHAPE_MISMATCH;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}

mltStatus mltLinearRegressionFit(
    mltLinearRegression* model, const mltMatrixF* x, const mltVectorF* y, const float learningRate, const size_t epochs
)
{
    if (!model || !x || !y)
        return MLT_STATUS_ERR_NULL_PTR;

    try
    {
        model->impl.fit(x->implMat, y->implVec, learningRate, epochs);
    }
    catch (const mlt::math::ShapeMismatchException&)
    {
        return MLT_STATUS_SHAPE_MISMATCH;
    }
    catch (...)
    {
        return MLT_STATUS_INTERNAL_ERROR;
    }

    return MLT_STATUS_SUCCESS;
}
