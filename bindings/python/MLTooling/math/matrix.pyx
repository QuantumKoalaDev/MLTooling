from libc.stddef cimport size_t
from ._matrix cimport *


from ..mlt_status import MltStatus, check_status
from MLTooling.core import Shape, Dtypes

cdef class Matrix:
    def __cinit__(self):
        self.c_mat_f = NULL


    def __init__(self, size_t rows, size_t cols, dtype: Dtypes = Dtypes.FLOAT32):
        cdef mltMatrixF* ptr = NULL
        cdef int status

        status = mltFwMatrixFCreate(rows, cols, &ptr)
        py_status = MltStatus(status)
        check_status(py_status)

        self.c_mat_f = <mltMatrixF*>ptr

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
        py_status = MltStatus(status)
        check_status(py_status)
        
        mat.c_mat_f = ptr
        
        return mat
    
    @classmethod
    def _from_ptr(cls, ptr):
        mat = Matrix(0,0)
        mat.c_mat_f = <mltMatrixF*>ptr

        return mat

    def __dealloc__(self):
        if self.c_mat_f != NULL:
            mltFwMatrixFDestroy(self.c_mat_f)
            self.c_mat_f = NULL

    def __getitem__(self, key):
        cdef size_t row, col
        cdef float val
        cdef int status

        if isinstance(key, tuple) and len(key) == 2:
            row = <size_t>key[0]
            col = <size_t>key[1]
        else:
            raise TypeError("Index must be a tuple(row, col)")

        status = mltFwMatrixFGet(self.c_mat_f, row, col, &val)

        py_status = MltStatus(status)
        check_status(py_status)

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

        status = mltFwMatrixFSet(self.c_mat_f, row, col, val)

        py_status = MltStatus(status)
        check_status(py_status)

    def __add__(self, other):
        cdef int status
        cdef mltMatrixF* result = NULL
        cdef Matrix input_other

        if isinstance(other, Matrix):
            input_other = <Matrix> other
            status = mltFwMatrixFAdd(self.c_mat_f, input_other.c_mat_f, &result)
        else:
            raise TypeError(f"Unsupported operand type for +: {type(other).__name__}")


        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)

    def __iadd__(self, other):
        cdef int status
        cdef Matrix input_other

        if isinstance(other, Matrix):
            input_other = <Matrix> other
            status = mltFwMatrixFAddInPlace(self.c_mat_f, input_other.c_mat_f)
        else:
            raise TypeError(f"Unsupported operand type for +=: {type(other).__name__}")

        py_status = MltStatus(status)
        check_status(py_status)

        return self

    def __mul__(self, other):
        cdef int status
        cdef mltMatrixF* result = NULL
        cdef Matrix input_other

        if isinstance(other, Matrix):
            input_other = <Matrix>other
            status = mltFwMatrixFMultiply(self.c_mat_f, input_other.c_mat_f, &result)
        else:
            raise TypeError(f"Unsupported operand type for *: {type(other).__name__}")
        
        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)
    
    def shape(self):
        cdef size_t rows
        cdef size_t cols
        cdef int status

        status = mltFwMatrixFRowCount(self.c_mat_f, &rows)

        py_status = MltStatus(status)
        check_status(py_status)

        status = mltFwMatrixFColCount(self.c_mat_f, &cols)
        py_status = MltStatus(status)
        check_status(py_status)

        return Shape(rows, cols)

    def clone(self):
        cdef int status
        cdef mltMatrixF* result = NULL

        status = mltFwMatrixFClone(self.c_mat_f, &result)
        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)

    def copy(self):
        cdef int status
        cdef mltMatrixF* result = NULL

        status = mltFwMatrixFCopy(self.c_mat_f, &result)
        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)

    def submatrix(self, start: Shape, count: Shape):
        cdef int status
        cdef mltMatrixF* result = NULL

        status = mltFwMatrixFSubmatrix(self.c_mat_f, start.rows, start.cols, count.rows, count.cols, &result)
        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)