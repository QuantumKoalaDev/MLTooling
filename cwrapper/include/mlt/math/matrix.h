#ifdef _WIN32
    #ifdef MLTOOLING_CWRAPPER_EXPORTS
        #define MLTOOLING_CWRAPPER __declspec(dllexport)
    #else
        #define MLTOOLING_CWRAPPER __declspec(dllimport)
    #endif
#else
    #define MLTOOLING_CWRAPPER
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
        MLT_STATUS_SHAPE_MISSMATCH
    } mltStatus;

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFCreate(size_t rows, size_t cols, mltMatrixF** out);
    MLTOOLING_CWRAPPER mltStatus
    mltFwMatrixFCreateFromBuff(size_t rows, size_t cols, const float* buff, size_t elemCount, mltMatrixF** out);
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFDestroy(mltMatrixF* mat);

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFSet(mltMatrixF* mat, size_t row, size_t col, float newVal);
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFGet(const mltMatrixF* mat, size_t row, size_t col, float* out);

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFRowCount(const mltMatrixF* mat, size_t* out);
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFColCount(const mltMatrixF* mat, size_t* out);

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFAdd(const mltMatrixF* a, const mltMatrixF* b, mltMatrixF** out);
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFAddInPlace(mltMatrixF* a, const mltMatrixF* b);
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFMultiply(const mltMatrixF* a, const mltMatrixF* b, mltMatrixF** out);

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFClone(const mltMatrixF* mat, mltMatrixF** out);
    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFCopy(const mltMatrixF* mat, mltMatrixF** out);

    MLTOOLING_CWRAPPER mltStatus mltFwMatrixFSubmatrix(
        const mltMatrixF* mat, size_t startRow, size_t startCol, size_t rowCount, size_t colCount, mltMatrixF** out
    );
#ifdef __cplusplus
}
#endif
