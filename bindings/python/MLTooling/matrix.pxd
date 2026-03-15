from ._matrix cimport mltMatrixF

cdef class Matrix:
    cdef mltMatrixF* c_mat