from libc.stddef cimport size_t
from ._matrix cimport (
    mltMatrixF,
    mltFwMatrixFCreate,
    mltFwMatrixFDestroy,
    mltFwMatrixFCreateFromBuff,
    mltFwMatrixFGet,
    mltFwMatrixFSet,
    mltFwMatrixFRowCount,
    mltFwMatrixFColCount,
    mltFwMatrixFAdd,
    mltStatus,
    MLT_STATUS_SUCCESS
)

cdef class Matrix:
    def __cinit__(self):
        self.c_mat = NULL


    def __init__(self, size_t rows, size_t cols):
        cdef mltMatrixF* ptr = NULL
        cdef int status

        status = mltFwMatrixFCreate(rows, cols, &ptr)
        
        if status != MLT_STATUS_SUCCESS:
            raise RuntimeError("Matrix allocations failed")

        self.c_mat = <mltMatrixF*>ptr

    @classmethod
    def from_buffer(cls, size_t rows, size_t cols, float [:] data):
        cdef Matrix mat = cls.__new__(cls)
        cdef mltMatrixF* ptr = NULL
        cdef int status

        if <size_t>data.shape[0] != rows * cols:
            raise ValueError("Buffer size mismatch")

        status = mltFwMatrixFCreateFromBuff(
            rows,
            cols,
            &data[0],
            data.shape[0],
            &ptr
        )

        if status != MLT_STATUS_SUCCESS:
            raise RuntimeError("Matrix allocation from buffer failed")
        
        mat.c_mat = ptr
        
        return mat
    
    @classmethod 
    def from_ptr(cls, ptr):
        cdef Matrix mat = cls.__new__(cls)
        mat.c_mat = ptr

        return mat

    def __dealloc__(self):
        if self.c_mat != NULL:
            mltFwMatrixFDestroy(self.c_mat)
            self.c_mat = NULL

    def __getitem__(self, key):
        cdef size_t row, col
        cdef float val
        cdef int status

        if isinstance(key, tuple) and len(key) == 2:
            row = <size_t>key[0]
            col = <size_t>key[1]
        else:
            raise TypeError("Index must be a tuple(row, col)")

        status = mltFwMatrixFGet(self.c_mat, row, col, &val)

        if status != MLT_STATUS_SUCCESS:
            raise RuntimeError("Matrix getter failed")

        return val
    
    def __setitem__(self, key, value):
        cdef size_t row, col
        cdef float val
        cdef int status

        if isinstance(key, tuple) and len(key) == 2:
            row = <size_t>key[0]
            col = <size_t>key[1]
        else:
            raise TypeError("Index must be a tuple(row, col)")

        val = <float>value

        status = mltFwMatrixFSet(self.c_mat, row, col, val)

        if status != MLT_STATUS_SUCCESS:
            raise RuntimeError("Matrix setter failed")
    
    def shape(self):
        cdef size_t rows
        cdef size_t cols
        cdef int status

        status = mltFwMatrixFRowCount(self.c_mat, &rows)

        if status != MLT_STATUS_SUCCESS:
            raise RuntimeError("Matrix row getter falied")

        status = mltFwMatrixFColCount(self.c_mat, &cols)

        if status != MLT_STATUS_SUCCESS:
            raise RuntimeError("Matrix col getter failed")

        return (rows, cols)

    def __add__(self, other):
        cdef int status
        cdef mltMatrixF* result = NULL
        cdef mltMatrixF* other = other.c_mat

        shape = self.shape()
        shape_other = other.shape()


        status = mltFwMatrixFAdd(self.c_mat, other, &result)

        if status != MLT_STATUS_SUCCESS:
            raise RuntimeError("Matrix additon failed")

        return Matrix.from_ptr(result)
