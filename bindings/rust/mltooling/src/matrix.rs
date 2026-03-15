use crate::ffi::{self, mltMatrixF, mltStatus};
use std::ptr;

pub struct MatrixF {
    ptr: *mut mltMatrixF,
}

impl MatrixF {
    pub fn new(rows: usize, cols: usize) -> Result<Self, mltStatus> {
        let mut ptr: *mut mltMatrixF = ptr::null_mut();
        let status = unsafe {
            ffi::mltFwMatrixFCreate(rows as _, cols as _, &mut ptr)
        };

        if status == mltStatus::MltStatusSuccess {
            Ok(Self {ptr})
        } else {
            Err(status)
        }
    }

    pub fn new_from_slice(rows: usize, cols: usize, buffer: &[f32]) -> Result<Self, mltStatus> {
        let mut ptr: *mut mltMatrixF = ptr::null_mut();
        let status = unsafe {
            ffi::mltFwMatrixFCreateFromBuff(rows as _, cols as _, buffer.as_ptr(), buffer.len() as _, &mut ptr)
        };

        if status == mltStatus::MltStatusSuccess {
            Ok(Self {ptr})
        } else {
            Err(status)
        }
    }

    pub fn get(&self, row: usize, cols: usize) -> Result<f32, mltStatus> {
        let mut val: f32 = 0.0;
        let status = unsafe {
            ffi::mltFwMatrixFGet(self.ptr, row as _, cols as _, &mut val)
        };

        if status == mltStatus::MltStatusSuccess {
            Ok(val)
        } else {
            Err(status)
        }
    }
}

impl Drop for MatrixF {
    fn drop(&mut self) {
        unsafe {
            if !self.ptr.is_null() {
                ffi::mltFwMatrixFDestroy(self.ptr);
            }
        }
    }
}
