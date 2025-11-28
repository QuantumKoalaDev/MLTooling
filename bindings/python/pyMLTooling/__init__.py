import ctypes
import pathlib
import sys

_lib_dir = pathlib.Path(__file__).parent / "_lib"

if (sys.platform == "win32"):
    _lib = ctypes.CDLL(_lib_dir / "MLToolingCapi.dll")
elif (sys.platform == "darwin"):
    _lib = ctypes.CDLL(_lib_dir / "libMLToolingCapi.dylib")
else:
    _lib = ctypes.CDLL(_lib_dir / "libMLToolingCapi.so")



#------------------------------------------
# Container - Shape Functions
#------------------------------------------
_lib.ct_shape_create.restype = ctypes.c_void_p
_lib.ct_shape_create.argtypes = [ctypes.c_ulong, ctypes.c_ulong]

_lib.ct_shape_destroy.restype = None
_lib.ct_shape_destroy.argtypes = [ctypes.c_void_p]

_lib.ct_shape_getRows.restype = ctypes.c_ulong
_lib.ct_shape_getRows.argtypes = [ctypes.c_void_p]

_lib.ct_shape_getCols.restype = ctypes.c_ulong
_lib.ct_shape_getCols.argtypes = [ctypes.c_void_p]

#------------------------------------------
# Container - Mat Functions
#------------------------------------------
_lib.ct_mat_create.restype = ctypes.c_void_p
_lib.ct_mat_create.argtypes = []

_lib.ct_mat_create_from_flat_array.restype = ctypes.c_void_p
_lib.ct_mat_create_from_flat_array.argtypes = [ctypes.POINTER(ctypes.c_float), ctypes.c_ulong, ctypes.c_ulong]

_lib.ct_mat_destroy.restype = None
_lib.ct_mat_destroy.argtypes = [ctypes.c_void_p]

_lib.ct_mat_copy_row.restype = None
_lib.ct_mat_copy_row.argtypes = [ctypes.c_void_p, ctypes.c_ulong, ctypes.c_void_p]

_lib.ct_mat_get_shape.restype = ctypes.c_void_p
_lib.ct_mat_get_shape.argtypes = [ctypes.c_void_p]

_lib.ct_mat_add_row.restype = None
_lib.ct_mat_add_row.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.c_ulong]

#------------------------------------------
# Models - LinearRegression Functions
#------------------------------------------

_lib.lr_create.restype = ctypes.c_void_p
_lib.lr_create.argtypes = []

_lib.lr_destroy.restype = None
_lib.lr_destroy.argtypes = [ctypes.c_void_p]

_lib.lr_fit.restype = None
_lib.lr_fit.argtypes = [ctypes.c_void_p, ctypes.c_void_p, ctypes.POINTER(ctypes.c_float), ctypes.c_ulong, ctypes.c_float, ctypes.c_ulong]

_lib.lr_predict.restype = ctypes.c_float
_lib.lr_predict.argtypes = [ctypes.c_void_p, ctypes.POINTER(ctypes.c_float), ctypes.c_ulong]