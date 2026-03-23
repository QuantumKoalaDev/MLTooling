from ._matrix cimport mltMatrixF, mltMatrixD

cdef class Matrix:
    cdef int _type
    cdef mltMatrixF* _c_mat_f
    cdef mltMatrixD* _c_mat_d
