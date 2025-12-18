from enum import IntEnum

class MltStatus(IntEnum):
    MLT_OK = 0
    MLT_ERR_NULL_PTR = 1
    MLT_ALLOCATION_FAILED = 2
    MLT_ERR_OUT_OF_RANGE = 3
    MLT_ERR_INTERNAL = 4

def checkStatus(status: MltStatus):
    match status:
        case MltStatus.MLT_OK:
            return
        case MltStatus.MLT_ERR_NULL_PTR:
            raise MltNullPtrError()
        case MltStatus.MLT_ALLOCATION_FAILED:
            raise MltAllocationFailedError()
        case MltStatus.MLT_ERR_INTERNAL:
            raise MltInternalError()
        case MltStatus.MLT_ERR_OUT_OF_RANGE:
            raise MltOutOfRangeError()
        case _:
            raise RuntimeError(f"Unknown MltStatus: {status}")
        



class MltNullPtrError(RuntimeError):
    """Exception raised when a NULL pointer is encountered in MLTooling C API."""
    def __init__(self, message: str = "Encountered NULL pointer in MLTooling C API"):
        super().__init__(message)

class MltAllocationFailedError(RuntimeError):
    """Exception raised when an allocation error is encountered in MLTooling C API."""
    def __init__(self, message: str = "Encountered allocation error in MLTooling C API"):
        super().__init__(message)

class MltInternalError(RuntimeError):
    """Exception raised when an internal error is encountered in MLTooling C API."""
    def __init__(self, message: str = "Encountered internal error in MLTooling C API"):
        super().__init__(message)

class MltOutOfRangeError(RuntimeError):
    """Exception raised when an out of range error is encountered in MLTooling C API."""
    def __init__(self, message: str = "Encountered out of range error in MLTooling C API") -> None:
        super().__init__(message)