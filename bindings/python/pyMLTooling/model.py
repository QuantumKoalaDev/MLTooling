from . import _lib
import ctypes

class LinearRegressionModel:
    def __init__(self):
        self._ptr = _lib.lr_create()

    def __del__(self):
        if hasattr(self, "_ptr") and self._ptr:
            _lib.lr_destroy(self._ptr)
            self._ptr = None