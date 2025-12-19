import ctypes
from typing import Iterator, Self
from dataclasses import dataclass

from . import lib
from .error import checkStatus, MltStatus

@dataclass(frozen=True)
class Shape:
    rows: int
    cols: int


class Mat:
    @classmethod
    def from_flat_array(cls, rows: int, cols: int, data: list[float]) -> Self:
        if rows <= 0 or cols <= 0:
            raise ValueError("rows and cols must be > 0")
        
        data_length = len(data)
        max_data_length = rows * cols

        if data_length > max_data_length:
            raise ValueError("Data is too large and does not fit the submitted amount of cols and rows")
        
        if data_length < max_data_length:
            data.extend([0] * (max_data_length - data_length))
        
        ArrayType = ctypes.c_float * max_data_length
        c_array = ArrayType(*data)

        mat_ptr = ctypes.c_void_p()
        status: MltStatus = lib.mlt_ct_mat_create_from_flat_array(rows, cols, c_array, ctypes.byref(mat_ptr))
        checkStatus(status)

        obj = cls.__new__(cls)
        obj._ptr = mat_ptr
        return obj

    @classmethod
    def _from_ptr(cls, ptr: ctypes.c_void_p) -> Self:
        obj = cls.__new__(cls)
        obj._ptr = ptr
        return obj

    def __init__(self, rows: int, cols: int, init_val: float = 0.0) -> None:
        """
        Constructor for Mat. 
        Wraps a C++ matrix via ctypes.
        - rows, cols: dimensions of the matrix.
        - init_val: the initial value of the whole matrix. Default: 0.0
        """
        mat_ptr = ctypes.c_void_p()
        status: MltStatus = lib.mlt_ct_mat_create_with_val(rows, cols, init_val, ctypes.byref(mat_ptr))
        checkStatus(status)
        self._ptr = mat_ptr
    
    def get_shape(self) -> Shape:
        """
        Return the shape of the matrix as a Shape dataclass.
        Uses the C API to query rows and columns.
        """
        rows = ctypes.c_ulong()
        status: MltStatus = lib.mlt_ct_mat_get_shape_rows(self._ptr, ctypes.byref(rows))
        checkStatus(status)

        cols = ctypes.c_ulong()
        status = lib.mlt_ct_mat_get_shape_cols(self._ptr, ctypes.byref(cols))
        checkStatus(status)

        return Shape(int(rows.value), int(cols.value))
    
    def get_row(self, row_idx: int) -> list[float]:
        """
        Returns a single row of the matrix as a Python list of floats.
        Uses a C array internally and copies data from the C++ matrix.
        """
        shape = self.get_shape()

        ArrayType = ctypes.c_float * shape.cols
        out_c_array = ArrayType()
        status: MltStatus = lib.mlt_ct_mat_copy_row(row_idx, self._ptr, out_c_array)
        checkStatus(status)

        return list(out_c_array)
    
    def append_row(self, row: list[float]) -> None:
        """
        Appends a row at the end of the matrix.
        """
        data_length = len(row)
        
        if data_length  == 0:
            raise ValueError("rows must not be empty") 

        ArrayType = ctypes.c_float * data_length
        c_array = ArrayType(*row)

        status: MltStatus = lib.mlt_ct_mat_append_row(len(row), c_array, self._ptr)
        checkStatus(status)

    def __str__(self) -> str:
        """
        Human-readable string representation of the matrix.
        Shows up to the first 5 rows; truncates if the matrix has more rows.
        """
        shape = self.get_shape()
        rows_list = [self.get_row(i) for i in range(min(shape.rows, 5))]
        s = "\n".join(str(row) for row in rows_list)
        
        if shape.rows > 5:
            s += f"\n... ({shape.rows}) rows total"
        
        return f"Mat {shape.rows}x{shape.cols}:\n{s}"
    
    def __repr__(self) -> str:
        """
        Official representation of the matrix.
        Shows first 5 rows for preview, along with matrix dimensions.
        Can be useful for debugging.
        """
        shape = self.get_shape()
        rows_preview = [self.get_row(i) for i in range(min(shape.rows, 5))]
        return f"Mat(data={rows_preview}, rows={shape.rows}, cols={shape.cols})"
    
    def __getitem__(self, key: tuple[int, int]) -> float:
        """
        Allows indexing the matrix:
        - mat[i, j] -> element at row i, column j
        - mat[i]    -> first row element at column i
        """
        if len(key) != 2:
            raise IndexError("Invalid Index")
        
        row, col = key

        item = ctypes.c_float()
        status: MltStatus = lib.mlt_ct_mat_get_item(row, col, self._ptr, ctypes.byref(item))
        checkStatus(status)

        return item.value

    def __setitem__(self, key: tuple[int, int], value: float) -> None:
        """
        Allows setting elements of the matrix:
        - mat[i, j] = value -> set element at row i, column j
        - mat[i] = value    -> set element in first row, column i
        """
        if len(key) != 2:
            raise IndexError("Invalid index")
        
        row, col = key

        status: MltStatus = lib.mlt_ct_mat_set_item(row, col, value, self._ptr)
        checkStatus(status)
        
    def __iter__(self) -> Iterator[list[float]]:
        """
        Allows iteration over the matrix by rows.
        Each iteration returns a list of floats representing a row.
        """
        shape = self.get_shape()
        
        for row_idx in range(shape.rows):
            yield self.get_row(row_idx)

    def __copy__(self) -> None:
        raise NotImplementedError("Mat cannot be shallow copied")
    
    def __deepcopy__(self) -> None:
        raise NotImplementedError("Mat cannot be copied")

    def __add__(self, other: "Mat") -> "Mat":
        mat_ptr = ctypes.c_void_p()
        status: MltStatus = lib.mlt_ct_mat_add(self._ptr, other._ptr, ctypes.byref(mat_ptr))
        checkStatus(status)
        return Mat._from_ptr(mat_ptr)
    
    def __iadd__(self, other: "Mat") -> "Mat":
        status: MltStatus = lib.mlt_ct_mat_add_in_place(self._ptr, other._ptr)
        checkStatus(status)
        return self

    def __mul__(self, other: "Mat") -> "Mat":
        mat_ptr = ctypes.c_void_p()
        status: MltStatus = lib.mlt_ct_mat_mul(self._ptr, other._ptr, ctypes.byref(mat_ptr))
        checkStatus(status)
        return Mat._from_ptr(mat_ptr)

    def __del__(self) -> None:
        """
        Destructor for the Mat object.
        Frees the underlying C++ matrix using the C API.
        """
        if hasattr(self, "_ptr") and self._ptr:
            lib.mlt_ct_mat_destroy(self._ptr)
            self._ptr = None
