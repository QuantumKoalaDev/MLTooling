#ifndef MLTOOLING_LINEAR_REGRESSION_H
#define MLTOOLING_LINEAR_REGRESSION_H

/**
  * @file linearRegression.h
  * @brief C FFI wrapper for MLTooling linear regression.
  *
  * General API rules:
  *  - All functions reaturn a status code of type `mltStatus`.
  *  - Objects returned via `**out` ar owned by the caller and must be destroyed with the appropriate destroyed function.
  *  - Output parameters must not be NULL unless explicitly stated.
  *  - On failure, output parameters are left unmodified.
  *
  * All C++ exceptions are caught inside the wrapper and converted to `mltStatus` values.
  */

#include <mlt/core/core.h>
#include <mlt/math/matrix.h>
#include <mlt/math/vector.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif
    typedef struct mltLinearRegression mltLinearRegression;
    
    /**
     * Create a new linear Regression object.
     *
     * @param[out] out The pointer to the linear regression object.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltLinearRegressionCreate(mltLinearRegression **out);
    /**
     * Destroy a existing linear Regression object.
     *
     * @param[in] model Pointer to a linear regression.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltLinearRegressionDestroy(mltLinearRegression* model);
    /**
     * Predict the result for a given vector.
     *
     * @param[in] model Pointer to a linear regression object.
     * @param[in] features Pointer to the feature vector.
     * @param[out] out The predicted result.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltLinearRegressionPredict(const mltLinearRegression* model, const mltVectorF* features, float* out);
    /**
     * Fits the model to given data.
     *
     * @param[in] model Pointer to a linear regression model.
     * @param[in] x Pointer to a matrix holding the features.
     * @param[in] y Pointer to a vector with results to x.
     * @param[in] learningRate The learning rate.
     * @param[in] epochs The training epochs.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_SHAPE_MISMATCH
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltLinearRegressionFit(mltLinearRegression* model, const mltMatrixF* x, const mltVectorF* y, float learningRate, size_t epochs);
#ifdef __cplusplus
}
#endif

#endif
