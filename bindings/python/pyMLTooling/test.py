# import ctypes
# import pathlib
# import sys


# _lib_dir = pathlib.Path(__file__).parent / "_lib"

# if (sys.platform == "win32"):
#     lib = ctypes.CDLL(_lib_dir / "MLToolingCabi.dll")
# elif (sys.platform == "darwin"):
#     lib = ctypes.CDLL(_lib_dir / "libMLToolingCabi.dylib")
# else:
#     lib = ctypes.CDLL(_lib_dir / libMLToolingCabi.so)


# lib.lr_create.restype = ctypes.c_void_p
# lib.lr_destroy.argtypes = [ctypes.c_void_p]

# model_ptr = lib.lr_create()
# print("created")
# lib.lr_destroy(model_ptr)
# print("destroyed")


# bindings/python/
# ├── pymltooling
# │   ├── __init__.py
# │   └── _lib  <-- hier soll die .so/.dll landen