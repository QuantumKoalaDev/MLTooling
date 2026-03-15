from libc.stddef import size_t

cdef extern from "math/matrix.h":

    cdef enum mltStatus:
        MLT_STATUS_SUCCESS = 0
        MLT_STATUS_ERR_NULL_PTR
        MLT_STATUS_INTERNAL_ERROR
        MLT_STATUS_ALLOCATION_FAILED
        MLT_STATUS_ALLOCATION_TOO_LARGE
        MLT_STATUS_OUT_OF_BOUNDS
        MLT_STATUS_SHAPE_MISMATCH

    cdef struct mltMatrixF

    int mltFwMatrixFCreate(size_t rows, size_t cols, mltMatrixF** out)
    int mltFwMatrixFDestroy(mltMatrixF* mat)
