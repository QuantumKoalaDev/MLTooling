import ctypes
import pathlib
import sys

_lib_dir = pathlib.Path(__file__).parent / "_lib"

if (sys.platform == "win32"):
    _lib = ctypes.CDLL(_lib_dir / "MLToolingCabi.dll")
elif (sys.platform == "darwin"):
    _lib = ctypes.CDLL(_lib_dir / "libMLToolingCabi.dylib")
else:
    _lib = ctypes.CDLL(_lib_dir / libMLToolingCabi.so)


_lib.lr_create.restype = ctypes.c_void_p
_lib.lr_destroy.argtypes = [ctypes.c_void_p]