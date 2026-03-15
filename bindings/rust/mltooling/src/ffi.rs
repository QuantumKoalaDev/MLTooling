use std::os::raw::{c_float};

#[cfg(unix)]
use std::os::raw::c_ulong as c_size_t;

#[cfg(windows)]
use std::os::raw::c_ulonglong as c_size_t;

#[repr(C)]
pub struct mltMatrixF {
    _private: [u8;0],
}

#[repr(C)]
#[derive(Debug, Copy, Clone, PartialEq, Eq)]
pub enum mltStatus {
    MltStatusSuccess = 0,
    MltStatusNullPtr,
    MltStatusInternalError,
    MltStatusAllocationFailed,
    MltStatusAllocationTooLarge
}

unsafe extern "C" {
    pub fn mltFwMatrixFCreate( row: c_size_t, cols: c_size_t, out: *mut *mut mltMatrixF) -> mltStatus;
    pub fn mltFwMatrixFCreateFromBuff(row: c_size_t, cols: c_size_t, buff: *const f32, elemCount: c_size_t, out: *mut *mut mltMatrixF) -> mltStatus;
    pub fn mltFwMatrixFDestroy(mat: *mut mltMatrixF) -> mltStatus;
    pub fn mltFwMatrixFGet(mat: *mut mltMatrixF, row: c_size_t, col: c_size_t, vald: *mut c_float) -> mltStatus;
}
