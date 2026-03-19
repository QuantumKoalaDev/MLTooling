from ._matrix cimport mltMatrixF, mltMatrixD

cdef class Matrix:
    cdef mltMatrixF* c_mat_f
