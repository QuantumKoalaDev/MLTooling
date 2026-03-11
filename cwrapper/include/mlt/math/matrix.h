#ifndef MLTOOLING_MATRIX_H
#define MLTOOLING_MATRIX_H

/**
 * @file matrix.h
 * @brief C FFI wrapper for MLTooling matrix operations.
 *
 * General API rules:
 *
 * - All functions return a status code of type `mltStatus`.
 * - Objects returned via `**out` are owned by the caller and must be destroyed with the appropriate destroy function.
 * - Output parameters must not be NULL unless explicitly stated.
 * - On failure, output parameters are left unmodified.
 *
 * All C++ exceptions are caught inside the wrapper and converted to `mltStatus` values.
 *
 */

#ifdef _WIN32
    #ifdef MLTOOLING_CWRAPPER_EXPORTS
        #define MLTOOLING_CWRAPPER __declspec(dllexport)
    #else
        #define MLTOOLING_CWRAPPER __declspec(dllimport)
    #endif
#else
    #define MLTOOLING_CWRAPPER __attribute__((visibility("default")))
#endif

#include <stddef.h>

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct mltMatrixF mltMatrixF;

    typedef enum
    {
        MLT_STATUS_SUCCESS = 0,
        MLT_STATUS_ERR_NULL_PTR,
        MLT_STATUS_INTERNAL_ERROR,
        MLT_STATUS_ALLOCATION_FAILED,
        MLT_STATUS_ALLOCATION_TOO_LARGE,
        MLT_STATUS_OUT_OF_BOUNDS,
        MLT_STATUS_SHAPE_MISMATCH
    } mltStatus;

    /**
     * Create a new float matrix.
     *
     * @param rows Number of rows.
     * @param cols Number of columns.
     * @param out  Receives the created matrix.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFCreate(size_t rows, size_t cols, mltMatrixF** out);
    /**
     * Create a new float matrix from a buffer.
     *
     * @param rows Number of rows.
     * @param cols Number of column.
     * @param out Receives the created matrix.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus
    mltFwMatrixFCreateFromBuff(size_t rows, size_t cols, const float* buff, size_t elemCount, mltMatrixF** out);
    /**
     * Destroy an existing float matrix.
     *
     * @param mat The matrix to destroy.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFDestroy(mltMatrixF* mat);

    /**
     * Sets the value at a specific positon in a float matrix.
     *
     * @param mat The float matix.
     * @param row The row index.
     * @param col The column index.
     * @param newVal The value to set at the given position.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_OUT_OF_BOUNDS
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFSet(mltMatrixF* mat, size_t row, size_t col, float newVal);
    /**
     * Gets the value at a specific position in a float matrix.
     *
     * @param mat The float matrix.
     * @param row The row index.
     * @param col The column index.
     * @param out Receives the value at the given position.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_OUT_OF_BOUNDS
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFGet(const mltMatrixF* mat, size_t row, size_t col, float* out);

    /**
     * Retrieves the number of rows in a float matrix.
     *
     * @param mat The float matrix.
     * @param out Receives the row count.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFRowCount(const mltMatrixF* mat, size_t* out);
    /**
     * Retrieves the number of columns in a float matrix.
     *
     * @param mat The float matrix.
     * @param out Receives the column count.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFColCount(const mltMatrixF* mat, size_t* out);

    /**
     * Adds two float matrices and returns the result in a newly allocated float matrix.
     *
     * @param a The first matrix.
     * @param b The second matrix.
     * @param out Retrieves the result of the addition.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFAdd(const mltMatrixF* a, const mltMatrixF* b, mltMatrixF** out);
    /**
     * Adds the second float matrix to the first matrix in place.
     *
     * @param a The matrix to be modified (first addend).
     * @param b The second matrix (addend).
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFAddInPlace(mltMatrixF* a, const mltMatrixF* b);
    /**
     * Multiplies two float matrices and stores the result in a newly allocated matrix.
     *
     * @param a   The first matrix (multiplicand).
     * @param b   The second matrix (multiplier).
     * @param out Receives the resulting matrix of the multiplication.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFMultiply(const mltMatrixF* a, const mltMatrixF* b, mltMatrixF** out);

    /**
     * Creates a deep copy of the given float matrix.
     * @brief Allocates a new buffer and duplicates all elements from the source matrix.
     *
     * @param mat The matrix to clone.
     * @param out Receives the newly allocated clone of the matrix.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFClone(const mltMatrixF* mat, mltMatrixF** out);
    /**
     * Creates a shallow copy of the given float matrix.
     * @brief Allocates a new matrix, but shares the underlying data buffer with the source.
     *
     * @param mat The source matrix to copy.
     * @param out Receives the newly allocated copy of the matrix.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFCopy(const mltMatrixF* mat, mltMatrixF** out);

    /**
     * Extracts a submatrix from the given float matrix.
     * @brief Allocates a new matrix view; the underlying data buffer is shared with the original matrix.
     *
     * @param mat       The source matrix.
     * @param startRow  The starting row index of the submatrix.
     * @param startCol  The starting column index of the submatrix.
     * @param rowCount  Number of rows in the submatrix.
     * @param colCount  Number of columns in the submatrix.
     * @param out       Receives the newly allocated submatrix.
     *
     * @retval MLT_STATUS_SUCCESS
     * @retval MLT_STATUS_ERR_NULL_PTR
     * @retval MLT_STATUS_SHAPE_MISMATCH
     * @retval MLT_STATUS_ALLOCATION_FAILED
     * @retval MLT_STATUS_ALLOCATION_TOO_LARGE
     * @retval MLT_STATUS_INTERNAL_ERROR
     *
     * @see mltStatus for error code descriptions.
     */
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFSubmatrix(
        const mltMatrixF* mat, size_t startRow, size_t startCol, size_t rowCount, size_t colCount, mltMatrixF** out
    );
#ifdef __cplusplus
}
#endif
#endif
