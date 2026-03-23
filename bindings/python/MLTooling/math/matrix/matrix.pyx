from libc.stddef cimport size_t
from ._matrix cimport *

from array import array

from MLTooling.core import Shape, Dtypes, typecode_to_dtype
from MLTooling.mlt_status import MltStatus, check_status

cdef class Matrix:
    def __cinit__(self):
        self._c_mat_f = NULL
        self._c_mat_d = NULL
        self._type = -1


    def __init__(self, size_t rows, size_t cols, dtype: Dtypes = Dtypes.FLOAT32):
        cdef mltMatrixF* ptr_f = NULL
        cdef mltMatrixD* ptr_d = NULL
        cdef int status

        if dtype == Dtypes.FLOAT32:
            status = mltFwMatrixFCreate(rows, cols, &ptr_f)
            py_status = MltStatus(status)
            check_status(py_status)
            self._c_mat_f = ptr_f
        elif dtype == Dtypes.FLOAT64:
            status = mltFwMatrixDCreate(rows, cols, &ptr_d)
            py_status = MltStatus(status)
            check_status(py_status)
            self._c_mat_d = ptr_d
        else:
            raise TypeError("Unknown type")
        
        self._type = dtype.value

    @classmethod
    def from_buffer(cls, size_t rows, size_t cols, data: array):
        cdef Matrix mat = cls.__new__(cls)
        cdef mltMatrixF* ptr_f = NULL
        cdef mltMatrixD* ptr_d = NULL
        cdef int status
        cdef float [:] c_data_float
        cdef double [:] c_data_double
        dtype = typecode_to_dtype(data)

        if len(data) == 0:
            raise ValueError("data must not be empty")

        if dtype == Dtypes.FLOAT32:
            c_data_float = data
            status = mltFwMatrixFCreateFromBuff(
                rows,
                cols,
                &c_data_float[0],
                c_data_float.shape[0],
                &ptr_f
            )
            py_status = MltStatus(status)
            check_status(py_status)
            mat._c_mat_f = ptr_f
            mat._type = Dtypes.FLOAT32.value
        elif dtype == Dtypes.FLOAT64:
            c_data_double = data
            status = mltFwMatrixDCreateFromBuff(
                rows,
                cols,
                &c_data_double[0],
                c_data_double.shape[0],
                &ptr_d
            )
            py_status = MltStatus(status)
            check_status(py_status)
            mat._c_mat_d = ptr_d
            mat._type = Dtypes.FLOAT64.value
        else:
            raise TypeError("Unknown type")
        
        return mat
    
    @classmethod
    def _from_ptr(cls, ptr):
        mat = Matrix(0,0)
        mat._c_mat_f = <mltMatrixF*>ptr

        return mat

    def __dealloc__(self):
        if self._c_mat_f != NULL:
            mltFwMatrixFDestroy(self._c_mat_f)
            self._c_mat_f = NULL
        
        if self._c_mat_d != NULL:
            mltFwMatrixDDestroy(self._c_mat_d)
            self._c_mat_d = NULL

    def __getitem__(self, key):
        cdef size_t row, col
        cdef float val_float
        cdef double val_double
        cdef int status

        if isinstance(key, tuple) and len(key) == 2:
            row = <size_t>key[0]
            col = <size_t>key[1]
        else:
            raise TypeError("Index must be a tuple(row, col)")

        if self._type == Dtypes.FLOAT32.value:
            status = mltFwMatrixFGet(self._c_mat_f, row, col, &val_float)
            py_status = MltStatus(status)
            check_status(py_status)
            return val_float
        elif self._type == Dtypes.FLOAT64.value:
            status = mltFwMatrixDGet(self._c_mat_d, row, col, &val_double)
            py_status = MltStatus(status)
            check_status(py_status)
            return val_double
        else:
            raise TypeError("Unknown type")
    
    def __setitem__(self, key, value):
        cdef size_t row, col
        cdef float val
        cdef int status

        if value == None:
            raise TypeError("value must not be None")

        if isinstance(key, tuple) and len(key) == 2:
            row = <size_t>key[0]
            col = <size_t>key[1]
        else:
            raise TypeError("Index must be a tuple(row, col)")

        if self._type == Dtypes.FLOAT32.value:
            val = <float>value
            status = mltFwMatrixFSet(self._c_mat_f, row, col, val)
            py_status = MltStatus(status)
            check_status(py_status)
        elif self._type == Dtypes.FLOAT64.value:
            val = <double>value
            status = mltFwMatrixDSet(self._c_mat_d, row, col, val)
            py_status = MltStatus(status)
            check_status(py_status)
        else:
            raise TypeError("Unknown type")

    def __add__(self, other):
        cdef int status
        cdef mltMatrixF* result_float = NULL
        cdef Matrix input_other

        if isinstance(other, Matrix):
            input_other = <Matrix> other
            status = mltFwMatrixFAdd(self._c_mat_f, input_other._c_mat_f, &result_float)
        else:
            raise TypeError(f"Unsupported operand type for +: {type(other).__name__}")


        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result_float)

    def __iadd__(self, other):
        cdef int status
        cdef Matrix input_other

        if isinstance(other, Matrix):
            input_other = <Matrix> other
            status = mltFwMatrixFAddInPlace(self._c_mat_f, input_other._c_mat_f)
        else:
            raise TypeError(f"Unsupported operand type for +=: {type(other).__name__}")

        py_status = MltStatus(status)
        check_status(py_status)

        return self

    def __matmul__(self, other):
        cdef int status
        cdef mltMatrixF* result = NULL
        cdef Matrix input_other

        if isinstance(other, Matrix):
            input_other = <Matrix>other
            status = mltFwMatrixFMultiply(self._c_mat_f, input_other._c_mat_f, &result)
        else:
            raise TypeError(f"Unsupported operand type for *: {type(other).__name__}")
        
        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)
    
    def shape(self):
        cdef size_t rows
        cdef size_t cols
        cdef int status

        if self._type == Dtypes.FLOAT32.value:
            status = mltFwMatrixFRowCount(self._c_mat_f, &rows)
            py_status = MltStatus(status)
            check_status(py_status)

            status = mltFwMatrixFColCount(self._c_mat_f, &cols)
            py_status = MltStatus(status)
            check_status(py_status)
        elif self._type == Dtypes.FLOAT64.value:
            status = mltFwMatrixDRowCount(self._c_mat_d, &rows)
            py_status = MltStatus(status)
            check_status(py_status)

            status = mltFwMatrixDColCount(self._c_mat_d, &cols)
            py_status = MltStatus(status)
            check_status(py_status)
        else:
            raise TypeError("Unknown type")

        return Shape(rows, cols)

    def clone(self):
        cdef int status
        cdef mltMatrixF* result = NULL

        status = mltFwMatrixFClone(self._c_mat_f, &result)
        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)

    def copy(self):
        cdef int status
        cdef mltMatrixF* result = NULL

        status = mltFwMatrixFCopy(self._c_mat_f, &result)
        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)

    def submatrix(self, start: Shape, count: Shape):
        cdef int status
        cdef mltMatrixF* result = NULL

        status = mltFwMatrixFSubmatrix(self._c_mat_f, start.rows, start.cols, count.rows, count.cols, &result)
        py_status = MltStatus(status)
        check_status(py_status)

        return Matrix._from_ptr(<object>result)