from libc.stddef cimport size_t
from ._matrix cimport (
    mltMatrixF,
    mltFwMatrixFCreate,
    mltFwMatrixFDestroy,
    mltStatus,
    MLT_STATUS_SUCCESS
)

cdef class Matrix:
    def __cinit__(self, size_t rows, size_t cols):
        cdef mltMatrixF* ptr = NULL
        cdef int status

        status = mltFwMatrixFCreate(rows, cols, &ptr)
        
        if status != MLT_STATUS_SUCCESS:
            raise RuntimeError("Matrix allocations failed")

        self.c_mat = ptr

    def __dealloc__(self):
        if self.c_mat != NULL:
            mltFwMatrixFDestroy(self.c_mat)
            self.c_mat = NULL
