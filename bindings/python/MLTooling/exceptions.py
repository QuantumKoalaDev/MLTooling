class MltBaseError(Exception):
    pass

class MltNullPtrError(MltBaseError):
    pass

class MltInternalError(MltBaseError):
    pass

class MltAllocationError(MltBaseError):
    pass

class MltAllocationTooLargeError(MltBaseError):
    pass

class MltOutOfBoundsError(MltBaseError):
    pass

class MltShapeMissmatchError(MltBaseError):
    pass
