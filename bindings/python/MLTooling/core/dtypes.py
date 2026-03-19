from enum import Enum

class Dtypes(Enum):
    FLOAT32 = 0
    FLOAT64 = 1
    UNKNOWN = 2

def typecode_to_dtype(arr):
    code = arr.typecode

    if code == "f":
        return Dtypes.FLOAT32
    elif code == "d":
        return Dtypes.FLOAT64
    else:
        return Dtypes.UNKNOWN
