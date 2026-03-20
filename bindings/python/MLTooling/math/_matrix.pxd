from libc.stddef import size_t

cdef extern from "math/matrix.h":

    cdef struct mltMatrixF
    cdef struct mltMatrixD

    int mltFwMatrixFCreate(size_t rows, size_t cols, mltMatrixF** out)
    int mltFwMatrixFCreateFromBuff(size_t rows, size_t cols, const float* buff, size_t elemCount, mltMatrixF** out)
    int mltFwMatrixFDestroy(mltMatrixF* mat)
    int mltFwMatrixFGet(const mltMatrixF* mat, size_t row, size_t col, float* out)
    int mltFwMatrixFSet(mltMatrixF* mat, size_t row, size_t col, float newVal)
    int mltFwMatrixFRowCount(const mltMatrixF* mat, size_t* out)
    int mltFwMatrixFColCount(const mltMatrixF* mat, size_t* out)
    int mltFwMatrixFAdd(const mltMatrixF* a, const mltMatrixF* b, mltMatrixF** out)
    int mltFwMatrixFAddInPlace(mltMatrixF* a, const mltMatrixF* b)
    int mltFwMatrixFMultiply(const mltMatrixF* a, const mltMatrixF* b, mltMatrixF** out)
    int mltFwMatrixFClone(const mltMatrixF* mat, mltMatrixF** out)
    int mltFwMatrixFCopy(const mltMatrixF* mat, mltMatrixF** out)
    int mltFwMatrixFSubmatrix(const mltMatrixF* mat, size_t startRow, size_t startCol, size_t rowCount, size_t colCount, mltMatrixF** out)

    int mltFwMatrixDCreate(size_t rows, size_t cols, mltMatrixD** out)
    int mltFwMatrixDCreateFromBuff(size_t rows, size_t cols, const double* buff, size_t elemCount, mltMatrixD** out)
    int mltFwMatrixDDestroy(mltMatrixD* mat)
    int mltFwMatrixDGet(const mltMatrixD* mat, size_t row, size_t col, double* out)
    int mltFwMatrixDSet(mltMatrixD* mat, size_t row, size_t col, double newVal)
    int mltFwMatrixDRowCount(const mltMatrixD* mat, size_t* out)
    int mltFwMatrixDColCount(const mltMatrixD* mat, size_t* out)
    int mltFwMatrixDAdd(const mltMatrixD* a, const mltMatrixD* b, mltMatrixD** out)
    int mltFwMatrixDAddInPlace(mltMatrixD* a, const mltMatrixD* b)
    int mltFwMatrixDMultiply(const mltMatrixD* a, const mltMatrixD* b, mltMatrixD** out)
    int mltFwMatrixDClone(const mltMatrixD* mat, mltMatrixD** out)
    int mltFwMatrixDCopy(const mltMatrixD* mat, mltMatrixD** out)
    int mltFwMatrixDSubmatrix(const mltMatrixD* mat, size_t startRow, size_t startCol, size_t rowCount, size_t colCount, mltMatrixD** out)