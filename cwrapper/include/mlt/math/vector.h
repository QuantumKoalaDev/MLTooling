#ifndef MLT_VECTOR_H
#define MLT_VECTOR_H

/**
  * @file vector.h
  * @brief C FFI wrapper for MLTooling vector operations.
  *
  * General API rules:
  *
  * - All functions return a status code of type `mltStatus`.
  * - Objects returned via `**out` are owned by the caller and must be destroyed with teh appropriate destroy function.
  * - Ouput parameters must not be NULL unless explicitly stated.
  * - On failure, output parameters are left unmodified.
  *
  * All C++ exceptions are caught inside the wrapper and converted to `mltStatus` vlaues.
  */

#include <mlt/core/core.h>

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct mltVectorF mltVectorF;
    typedef struct mltVectorD mltVectorD;

    /**
     * Create a new float vector.
     *
     * @param[in] size Vector length.
     * @param[out] out Receives a pointer to the created vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFCreate(size_t size, mltVectorF** out);
    /**
     * Create a new float vector from a buffer.
     *
     * @param[in] size Vector length.
     * @param[in] buff The buffer from which the vector is created.
     * @param[out] out Receives a pointer to the created vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFCreateFromBuff(size_t size, const float* buff, mltVectorF** out);
    /**
     * Destroy an existing float vector.
     *
     * @param[in] vec The vector to destroy.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFDestroy(mltVectorF* vec);
    /**
     * Sets the value at a specific position in a float vector.
     *
     * @param[in] vec Pointer to the float vector.
     * @param[in] pos The position index.
     * @param[in] newVal The value to set at the given position.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_OUT_OF_BOUNDS
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFSet(mltVectorF* vec, size_t pos, float newVal);
    /**
     * Gets the value at a specific position in a float vector.
     *
     * @param[in] vec Pointer to the float vector.
     * @param[in] pos The position index.
     * @param[out] out Receives the value at the given position.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_OUT_OF_BOUNDS
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFGet(const mltVectorF* vec, size_t pos, float* out);
    /**
     * Gets the length of the float vector.
     *
     * @param[in] vec Pointer to the float vector.
     * @param[out] out Receives the length of the float vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFLength(mltVectorF* vec, size_t* out);
    /**
     * Checks whether the float vector is transposed.
     *
     * @param[in] vec Pointer to the float vector.
     * @param[out] out Set to 1 if the vector is transposed, 0 otherwise.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFIsTransposed(mltVectorF* vec, int* out);
    /**
     * Transposes the float vector.
     *
     * @param[in] vec Pointer to the float vector.
     * 
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFTranspose(mltVectorF* vec);
    /**
     * Adds two float vectors and receives the result in a newly allocated float vector.
     *
     * @param[in] a Pointer to float vector.
     * @param[in] b Pointer to float vector.
     * @param[out] out Receives a pointer to the newly allocated result vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFAdd(const mltVectorF* a, const mltVectorF* b, mltVectorF** out);
    /**
     * Adds two float vectors in place.
     *
     * @param[in] Pointer to float vector.
     * @param[in] Pointer to float vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFAddInPlace(mltVectorF* a, const mltVectorF* b);
    /**
     * Subtracts two float vectors and receives the result in a newly allocated float vector.
     *
     * @param[in] a Pointer to float vector.
     * @param[in] b Pointer to float vector.
     * @param[out] out Receives a pointer to the newly allocated result vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFSubtract(const mltVectorF* a, const mltVectorF* b, mltVectorF** out);
    /**
     * Subtracts two float vectors in place.
     *
     * @param[in] a Pointer to float vector.
     * @param[in] b Pointer to float vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFSubtractInPlace(mltVectorF* a, const mltVectorF* b);
    /**
     * Multiplys a float vector with a scalar and receives the newly allocated result vector.
     *
     * @param[in] vec Pointer to float vector.
     * @param[in] scalar The multiplier.
     * @param[out] Receives a pointer to the newly allocated float vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFMulScalar(const mltVectorF* vec, float scalar, mltVectorF* out);
    /**
     * Multiplys a float vector with a scalar in place.
     *
     * @param[in] vec Pointer to float vec.
     * @param[in] scalar The multiplier.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFMulScalarInPlace(mltVectorF* vec, float scalar);
    /**
     * Computes the float vectors dot product.
     *
     * @param[in] a Pointer to a float vector.
     * @param[in] b Pointer to a float vector.
     * @param[out] out Receives the comuted dot product.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFDot(const mltVectorF* a, const mltVectorF* b, float* out);
    /**
     * Computes the element-wise (Hadamard) product of two float vectors.
     *
     * @param[in] a First input vector.
     * @param[in] b Scond input vector.
     * @param[out] out Receives a pointer to the newly allocated float vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFHadamard(const mltVectorF* a, const mltVectorF* b, mltVectorF** out);
    /**
     * Receive a shallow copy of the float vector.
     *
     * @param[in] vec Pointer to a float vector.
     * @param[out] out Receives a pointer to the newly allocated float vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFCopy(const mltVectorF* vec, mltVectorF** out);
    /**
     * Receive a deep copy of the float vector.
     *
     * @param[in] vec Pointer to a float vector.
     * @param[out] out Receives a pointer to the newly allocated float vector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFClone(const mltVectorF* vec, mltVectorF** out);
    /**
     * Receive a subvector with the given parameters.
     *
     * @param[in] vec Pointer to a float vector.
     * @param[in] pos The start position for the subvector.
     * @param[in] length The length of the subvector.
     * @param[out] out Receives a pointer to the newly allocated subvector.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_OUT_OF_BOUNDS
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code description.
     */
    MLTOOLING_CWRAPPER mltStatus mltVectorFSubvector(const mltVectorF* vec, size_t pos, size_t length, mltVectorF** out);

#ifdef __cplusplus
}
#endif

#endif
