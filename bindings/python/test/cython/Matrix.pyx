# Matrix.pyx
from Matrix cimport mltMatrixF, mltFwMatrixFCreate, mltFwMatrixFDestroy

cdef class Matrix:
    cdef mltMatrixF* c_mat

    def __cinit__(self, size_t rows, size_t cols):
        c_mat_ptr = <mltMatrixF*>NULL
        mltFwMatrixFCreate(rows, cols, &c_mat_ptr)
        self.c_mat = c_mat_ptr

    def __dealloc__(self):
        if self.c_mat != NULL:
            mltFwMatrixFDestroy(self.c_mat)
