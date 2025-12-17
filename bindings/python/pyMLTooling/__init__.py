import ctypes
import pathlib
import sys

_lib_dir = pathlib.Path(__file__).parent / "_lib"

if (sys.platform == "win32"):
    lib = ctypes.CDLL(_lib_dir / "MLToolingCapi.dll")
elif (sys.platform == "darwin"):
    lib = ctypes.CDLL(_lib_dir / "libMLToolingCapi.dylib")
else:
    lib = ctypes.CDLL(_lib_dir / "libMLToolingCapi.so")

#------------------------------------------
# Container - Mat Functions
#------------------------------------------
lib.ct_mat_create_from_flat_array.restype = ctypes.c_void_p
lib.ct_mat_create_from_flat_array.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.c_ulong, ctypes.c_ulong]

lib.ct_mat_destroy.restype = None
lib.ct_mat_destroy.argtypes = [ctypes.c_void_p]

lib.ct_mat_get_shape_rows.restype = ctypes.c_ulong
lib.ct_mat_get_shape_rows.argtypes = [ctypes.c_void_p]

lib.ct_mat_get_shape_cols.restype = ctypes.c_ulong
lib.ct_mat_get_shape_cols.argtypes = [ctypes.c_void_p]

lib.ct_mat_copy_row.restype = None
lib.ct_mat_copy_row.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.c_void_p]

lib.ct_mat_add_row.restype = None
lib.ct_mat_add_row.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_ulong]

lib.ct_mat_get_item.restype = ctypes.c_float
lib.ct_mat_get_item.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.c_ulong]

lib.ct_mat_set_item.restype = None
lib.ct_mat_set_item.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.c_ulong, ctypes.c_float]

#------------------------------------------
# Models - LinearRegression Functions
#------------------------------------------

lib.lr_create.restype = ctypes.c_void_p
lib.lr_create.argtypes = []

lib.lr_destroy.restype = None
lib.lr_destroy.argtypes = [ctypes.c_void_p]

lib.lr_fit.restype = None
lib.lr_fit.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_float), ctypes.c_ulong, ctypes.c_float, ctypes.c_ulong]

lib.lr_predict.restype = ctypes.c_float
lib.lr_predict.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_float), ctypes.c_ulong]