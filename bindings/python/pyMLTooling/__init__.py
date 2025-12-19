from ctypes import CDLL, c_ulong, c_float, POINTER, c_int, c_void_p
import pathlib
import sys

_lib_dir = pathlib.Path(__file__).parent / "_lib"

if (sys.platform == "win32"):
    lib = CDLL(_lib_dir / "MLToolingCapi.dll")
elif (sys.platform == "darwin"):
    lib = CDLL(_lib_dir / "libMLToolingCapi.dylib")
else:
    lib = CDLL(_lib_dir / "libMLToolingCapi.so")

#------------------------------------------
# Container - Mat Functions
#------------------------------------------
lib.mlt_ct_mat_create_with_val.argtypes = [
    c_ulong,
    c_ulong,
    c_float,
   POINTER(c_void_p)
]
lib.mlt_ct_mat_create_with_val.restype = c_int

lib.mlt_ct_mat_create_from_flat_array.argtypes = [
    c_ulong,
    c_ulong,
    POINTER(c_float),
    POINTER(c_void_p)
]
lib.mlt_ct_mat_create_with_val.restype = c_int

lib.mlt_ct_mat_destroy.argtypes = [c_void_p]
lib.mlt_ct_mat_destroy.restype = c_int

lib.mlt_ct_mat_get_shape_rows.argtypes = [c_void_p, POINTER(c_ulong)]
lib.mlt_ct_mat_get_shape_rows.restype = c_int

lib.mlt_ct_mat_get_shape_cols.argtypes = [c_void_p, POINTER(c_ulong)]
lib.mlt_ct_mat_get_shape_cols.restype = c_int

lib.mlt_ct_mat_copy_row.argtypes = [
    c_ulong,
    c_void_p,
    POINTER(c_float)
]
lib.mlt_ct_mat_copy_row.restype = c_int

lib.mlt_ct_mat_append_row.argtypes = [
    c_ulong,
    POINTER(c_float),
    c_void_p
]
lib.mlt_ct_mat_append_row.restype = c_int

lib.mlt_ct_mat_get_item.argtypes = [
    c_ulong,
    c_ulong,
    c_void_p,
    POINTER(c_float)
]
lib.mlt_ct_mat_get_item.restype = c_int

lib.mlt_ct_mat_set_item.argtypes = [
    c_ulong,
    c_ulong,
    c_float,
    c_void_p
]
lib.mlt_ct_mat_set_item.restype = c_int

lib.mlt_ct_mat_add.argtypes = [
    c_void_p,
    c_void_p,
    POINTER(c_void_p)
]
lib.mlt_ct_mat_add.restype = c_int

lib.mlt_ct_mat_add_in_place.argtypes = [c_void_p, c_void_p]
lib.mlt_ct_mat_add_in_place.restype = c_int

lib.mlt_ct_mat_mul.argtypes = [
    c_void_p,
    c_void_p,
    POINTER(c_void_p)
]
lib.mlt_ct_mat_mul.restype = c_int

#------------------------------------------
# Models - LinearRegression Functions
#------------------------------------------

lib.lr_create.restype = c_void_p
lib.lr_create.argtypes = []

lib.lr_destroy.restype = None
lib.lr_destroy.argtypes = [c_void_p]

lib.lr_fit.restype = None
lib.lr_fit.argtypes = [c_void_p, c_void_p, POINTER(c_float), c_ulong, c_float, c_ulong]

lib.lr_predict.restype = c_float
lib.lr_predict.argtypes = [c_void_p, POINTER(c_float), c_ulong]