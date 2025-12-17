from . import lib
from .container import Mat
import ctypes

class LinearRegressionModel:
    def __init__(self):
        self._ptr = lib.lr_create()

    def __del__(self):
        if hasattr(self, "_ptr") and self._ptr:
            lib.lr_destroy(self._ptr)
            self._ptr = None
    
    def fit(self, x_data: Mat, y_data: list[float], learning_rate: float, epochs: int):
        ArrayType = ctypes.c_float * len(y_data)
        c_array = ArrayType(*y_data)

        lib.lr_fit(self._ptr, x_data._ptr, c_array, len(y_data), learning_rate, epochs)

    def predict(self, x_features: list[float]) -> float:
        ArrayType = ctypes.c_float * len(x_features)
        c_array = ArrayType(*x_features)
        prediction = lib.lr_predict(self._ptr, c_array, len(x_features))
        
        return prediction
