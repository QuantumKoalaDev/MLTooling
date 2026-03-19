from enum import Enum

from .exceptions import *

class MltStatus(Enum):
    SUCCESS = 0
    NULL_PTR = 1
    INTERNAL_ERROR = 2
    ALLOCATION_FAILED = 3
    ALLOCATION_TOO_LARGE = 4
    OUT_OF_BOUNDS = 5
    SHAPE_MISSMATCH = 6

def check_status(stat: MltStatus):
    match(stat):
        case MltStatus.SUCCESS: return
        case MltStatus.NULL_PTR: raise MltNullPtrError()
        case MltStatus.INTERNAL_ERROR: raise MltInternalError()
        case MltStatus.ALLOCATION_FAILED: raise MltAllocationError()
        case MltStatus.ALLOCATION_TOO_LARGE: raise MltAllocationTooLargeError()
        case MltStatus.OUT_OF_BOUNDS: raise MltOutOfBoundsError()
        case MltStatus.SHAPE_MISSMATCH: raise MltShapeMissmatchError()
        case _: raise ValueError("Unknown status code")