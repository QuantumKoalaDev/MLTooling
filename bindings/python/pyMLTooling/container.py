import ctypes
from typing import Iterator
from dataclasses import dataclass
from . import lib

@dataclass(frozen=True)
class Shape:
    rows: int
    cols: int


class Mat:
    def __init__(self, data: list[float] | None = None, rows: int = 0, cols: int = 0):
        """
        Constructor for Mat.
        Wraps a C++ matrix via ctypes.
        - data: flat list of floats
        - rows, cols: dimensions of the matrix
        """
        if data is None or rows <= 0 or cols <= 0:
            raise ValueError("For the Mat constructor data, rows and cols must be provided")

        data_length: int = len(data)
        max_data_lenght: int = rows * cols

        if data_length > max_data_lenght:
            raise ValueError("Data is too large and does not fit the submitted amount of cols and rows")

        if data_length > max_data_lenght:
            for _ in range(data_length, max_data_lenght):
                data.append(0)
        
        ArrayType = ctypes.c_float * max_data_lenght
        c_array = ArrayType(*data)
        self._ptr = lib.ct_mat_create_from_flat_array(c_array, rows, cols)

    def get_shape(self) -> Shape:
        """
        Return the shape of the matrix as a Shape dataclass.
        Uses the C API to query rows and columns.
        """
        rows: int = lib.ct_mat_get_shape_rows(self._ptr)
        cols : int = lib.ct_mat_get_shape_cols(self._ptr)
        return Shape(rows, cols)
    
    def get_row(self, row_idx: int) -> list[float]:
        """
        Returns a single row of the matrix as a Python list of floats.
        Uses a C array internally and copies data from the C++ matrix.
        """
        shape = self.get_shape()

        ArrayType = ctypes.c_float * shape.cols
        out_c_array = ArrayType()
        lib.ct_mat_copy_row(self._ptr, row_idx, out_c_array)

        return list(out_c_array)
    
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
    
    def __getitem__(self, key: int | tuple[int, int]) -> float:
        """
        Allows indexing the matrix:
        - mat[i, j] -> element at row i, column j
        - mat[i]    -> first row element at column i
        """
        if isinstance(key, tuple) and len(key) == 2:
            row, col = key
            return lib.ct_mat_get_item(self._ptr, row, col)
        elif isinstance(key, int):
            return lib.ct_mat_get_item(self._ptr, 0, key)
        else:
            raise IndexError("Invalid index")

    def __setitem__(self, key: int | tuple[int, int], value: float) -> None:
        """
        Allows setting elements of the matrix:
        - mat[i, j] = value -> set element at row i, column j
        - mat[i] = value    -> set element in first row, column i
        """
        if isinstance(key, tuple) and len(key) == 2:
            row, col = key
            lib.ct_mat_set_item(self._ptr, row, col, value)
        elif isinstance(key, int):
            lib.ct_mat_set_item(self._ptr, 0, key, value)
        else:
            raise IndexError("Invalid index")
        
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

    def __del__(self) -> None:
        """
        Destructor for the Mat object.
        Frees the underlying C++ matrix using the C API.
        """
        if hasattr(self, "_ptr") and self._ptr:
            lib.ct_mat_destroy(self._ptr)
            self._ptr = None
