import ctypes
from . import _lib

class Shape:
    def __init__(self, rows: int, cols: int):
        if rows is not None and cols is not None:
            self._ptr = _lib.ct_shape_create(rows, cols)
        else:
            raise ValueError("Must provide either ptr or rows and cols")
    
    @classmethod
    def from_ptr(cls, ptr):
        obj = cls.__new__(cls)
        obj._ptr = ptr
        return obj

    def __del__(self):
        if hasattr(self, "_ptr") and self._ptr:
            _lib.ct_shape_destroy(self._ptr)
            self._ptr = None

    @property
    def rows(self):
        return _lib.ct_shape_getRows(self._ptr)
    
    @property
    def cols(self):
        return _lib.ct_shape_getCols(self._ptr)
    
class Mat:
    def __init__(self, data: list[float] = None, rows: int = None, cols: int = None):
        if data is None:
            self._ptr = _lib.ct_mat_create()
        else:
            ArrayType = ctypes.c_float * len(data)
            c_array = ArrayType(*data)
            self._ptr = _lib.ct_mat_create_from_flat_array(c_array, rows, cols)

    def __del__(self):
        if hasattr(self, "_ptr") and self._ptr:
            _lib.ct_mat_destroy
            self._ptr = None

    def get_shape(self) -> Shape:
        shape_ptr = _lib.ct_mat_get_shape(self._ptr)
        return Shape.from_ptr(shape_ptr)

    def get_row(self, row_index: int) -> list:
        shape = self.get_shape()
        cols = shape.cols

        ArrayType = ctypes.c_float * cols
        out_array = ArrayType()

        _lib.ct_mat_copy_row(self._ptr, row_index, ctypes.cast(out_array, ctypes.c_void_p))

        return list(out_array)
