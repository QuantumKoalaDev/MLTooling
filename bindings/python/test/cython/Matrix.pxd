# Matrix.pxd
ctypedef unsigned long size_t

cdef extern from "math/matrix.h":
    cdef struct mltMatrixF:
        pass

    int mltFwMatrixFCreate(size_t rows, size_t cols, mltMatrixF** out)
    int mltFwMatrixFDestroy(mltMatrixF* mat)
