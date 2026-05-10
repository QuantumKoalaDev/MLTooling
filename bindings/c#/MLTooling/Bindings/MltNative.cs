using System.Runtime.InteropServices;

namespace MLTooling.Bindings;
using MLTooling.Core.Handles;

using size_t = UIntPtr;

internal enum MltStatus
{
    SUCCESS = 0,
    NULL_PTR,
    INTERNAL_ERROR,
    ALLOCATION_FAILED,
    ALLOCATION_TOO_LARGE,
    OUT_OF_BOUNDS,
    SHAPE_MISSMATCH
}

[StructLayout(LayoutKind.Sequential)]
internal struct MltShape
{
    public size_t rows;
    public size_t cols;
}

internal static class MltNative
{
    private const string _DLL = "MLToolingCwrapper";
    private const CallingConvention _conv = CallingConvention.Cdecl;


    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFCreate(
            size_t rows,
            size_t cols,
            out MatrixFHandle matrix
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFCreateFromBuff(
        size_t rows,
        size_t cols,
        IntPtr buff,
        size_t elemCount,
        out MatrixFHandle matrix
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFDestroy(IntPtr mat);

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFSet(
            MatrixFHandle mat,
            size_t row,
            size_t col,
            float newVal
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFGet(
            MatrixFHandle mat,
            size_t row,
            size_t col,
            out float val
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFRowCount(MatrixFHandle mat, out size_t rowCount);

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFColCount(MatrixFHandle mat, out size_t colCount);

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int  mltFwMatrixFAdd(
        MatrixFHandle a,
        MatrixFHandle b,
        out MatrixFHandle mat
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFAddInPlace(
        MatrixFHandle a,
        MatrixFHandle b
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFMultiply(
        MatrixFHandle a,
        MatrixFHandle b,
        out MatrixFHandle mat
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFClone(
        MatrixFHandle mat,
        out MatrixFHandle result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFCopy(
        MatrixFHandle mat,
        out MatrixFHandle result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltFwMatrixFSubmatrix(
        MatrixFHandle mat,
        size_t startRow,
        size_t startCol,
        size_t rowCount,
        size_t colCount,
        out MatrixFHandle result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFCreate(
        size_t size,
        out VectorFHandle result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFCreateFromBuff(
        size_t size,
        IntPtr buff,
        out VectorFHandle vec
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFDestroy(IntPtr vec);

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFSet(
        VectorFHandle vec,
        size_t pos,
        float newVal
    );

    [DllImport(_DLL, CallingConvention  =_conv)]
    internal static extern int mltVectorFGet(
        VectorFHandle vec,
        size_t pos,
        out float val
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFLength(
        VectorFHandle vec,
        out size_t length
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFIsTransposed(
        VectorFHandle vec,
        out int isTransposed
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFTranspose(VectorFHandle vec);

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFAdd(
            VectorFHandle a,
            VectorFHandle b,
            out VectorFHandle c
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFAddInPlace(
            VectorFHandle a,
            VectorFHandle b
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFSubtract(
            VectorFHandle a,
            VectorFHandle b,
            out VectorFHandle c
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFSubtractInPlace(
            VectorFHandle a,
            VectorFHandle b
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFMulScalar(
            VectorFHandle vec,
            float scalar,
            out VectorFHandle result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFMulScalarInPlace(
            VectorFHandle vec,
            float scalar
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFDot(
            VectorFHandle a,
            VectorFHandle b,
            out float result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFHadamard(
            VectorFHandle a,
            VectorFHandle b,
            out VectorFHandle c
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFCopy(
            VectorFHandle vec,
            out VectorFHandle result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFClone(
            VectorFHandle vec,
            out VectorFHandle result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltVectorFSubvector(
            VectorFHandle vec,
            size_t pos,
            size_t length,
            out VectorFHandle subvec
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltLinearRegressionCreate(
            out LinearRegressionHandle model
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltLinearRegressionDestroy(
            IntPtr model
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltLinearRegressionPredict(
            LinearRegressionHandle model,
            VectorFHandle features,
            out float result
    );

    [DllImport(_DLL, CallingConvention = _conv)]
    internal static extern int mltLinearRegressionFit(
            LinearRegressionHandle model,
            MatrixFHandle x,
            VectorFHandle y,
            float learningRate,
            size_t epochs
    );
}
