using MLTooling.Core.Handles;


namespace MLTooling.Bindings;

internal static class MltWrapper
{
    public static MatrixFHandle MatrixFCreate(ulong rows, ulong cols)
    {
        MatrixFHandle resultHandle;

        MltStatus status = (MltStatus)MltNative.mltFwMatrixFCreate(
            (UIntPtr)rows,
            (UIntPtr)cols,
            out resultHandle
        );

        MltError.ThrowIfError(status);

        return resultHandle;
    }

    public static MatrixFHandle MatrixFCreateFromBuff(float[] data, ulong rows, ulong cols)
    {
        MatrixFHandle resultHandle;
        MltStatus status;

        unsafe
        {
            fixed (float* p = data)
            {
                status = (MltStatus)MltNative.mltFwMatrixFCreateFromBuff(
                    (UIntPtr)rows,
                    (UIntPtr)cols,
                    (IntPtr)p,
                    (UIntPtr)data.Length,
                    out resultHandle
                );
            }
        }

        MltError.ThrowIfError(status);

        return resultHandle;
    }

    public static float MatrixFGet(MatrixFHandle handle, ulong row, ulong col)
    {
        float val;

        MltStatus status = (MltStatus)MltNative.mltFwMatrixFGet(
            handle,
            (UIntPtr)row,
            (UIntPtr)col,
            out val
        );

        MltError.ThrowIfError(status);

        return val;
    }

    public static void MatrixFSet(MatrixFHandle handle, ulong row, ulong col, float val)
    {
        MltStatus status = (MltStatus)MltNative.mltFwMatrixFSet(
            handle,
            (UIntPtr)row,
            (UIntPtr)col,
            val
        );

        MltError.ThrowIfError(status);
    }

    public static MatrixFHandle MatrixFAdd(MatrixFHandle handle, MatrixFHandle otherHandle)
    {
        MatrixFHandle resultHandle;
        MltStatus status = (MltStatus)MltNative.mltFwMatrixFAdd(handle, otherHandle, out resultHandle);
        MltError.ThrowIfError(status);

        return resultHandle;
    }

    public static void MatrixFAddInPlace(MatrixFHandle handle, MatrixFHandle otherHandle)
    {
        MltStatus status = (MltStatus)MltNative.mltFwMatrixFAddInPlace(handle, otherHandle);
        MltError.ThrowIfError(status);
    }

    public static MatrixFHandle MatrixFMultiply(MatrixFHandle handle, MatrixFHandle otherHandle)
    {
        MatrixFHandle resultHandle;
        MltStatus status = (MltStatus)MltNative.mltFwMatrixFMultiply(handle, otherHandle, out resultHandle);
        MltError.ThrowIfError(status);

        return resultHandle;
    }

    public static MatrixFHandle MatrixFCopy(MatrixFHandle handle)
    {
        MatrixFHandle resultHandle;
        MltStatus status = (MltStatus)MltNative.mltFwMatrixFCopy(handle, out resultHandle);
        MltError.ThrowIfError(status);

        return resultHandle;
    }

    public static MatrixFHandle MatrixFClone(MatrixFHandle handle)
    {
        MatrixFHandle resultHandle;
        MltStatus status = (MltStatus)MltNative.mltFwMatrixFClone(handle, out resultHandle);
        MltError.ThrowIfError(status);

        return resultHandle;
    }

    public static MatrixFHandle MatrixFSubmatrix(
        MatrixFHandle handle,
        ulong startRow,
        ulong startCol,
        ulong rowCount,
        ulong colCount
    )
    {
        MatrixFHandle resultHandle;

        MltStatus status = (MltStatus)MltNative.mltFwMatrixFSubmatrix(
            handle,
            (UIntPtr)startRow,
            (UIntPtr)startCol,
            (UIntPtr)rowCount,
            (UIntPtr)colCount,
            out resultHandle
        );

        MltError.ThrowIfError(status);

        return resultHandle;
    }

    public static MltShape MatrixFGetShape(MatrixFHandle handle)
    {
        UIntPtr rows;
        UIntPtr cols;
        MltStatus status;

        status = (MltStatus)MltNative.mltFwMatrixFRowCount(handle, out rows);
        MltError.ThrowIfError(status);

        status = (MltStatus)MltNative.mltFwMatrixFColCount(handle, out cols);
        MltError.ThrowIfError(status);

        MltShape shape = new MltShape();
        shape.cols = cols;
        shape.rows = rows;

        return shape;
    }

    public static VectorFHandle VectorFCreate(ulong size)
    {
        VectorFHandle vecHandle;
        
        MltStatus status = (MltStatus)MltNative.mltVectorFCreate((UIntPtr) size, out vecHandle);
        MltError.ThrowIfError(status);

        return vecHandle;
    }

    public static VectorFHandle VectorFCreateFromBuff(float[] data, ulong size)
    {
        VectorFHandle vecHandle;
        MltStatus status;
        
        unsafe
        {
            fixed (float* p = data)
            {
                status = (MltStatus)MltNative.mltVectorFCreateFromBuff(
                    (UIntPtr)size,
                    (IntPtr)p,
                    out vecHandle
                );
            }
        }

        MltError.ThrowIfError(status);

        return vecHandle;
    }

    public static void VectorFSet(VectorFHandle handle, ulong pos, float val)
    {
        MltStatus status = (MltStatus)MltNative.mltVectorFSet(handle, (UIntPtr)pos, val);
        MltError.ThrowIfError(status);
    }

    public static float VectorFGet(VectorFHandle handle, ulong pos)
    {
        float val;

        MltStatus status = (MltStatus)MltNative.mltVectorFGet(
            handle,
            (UIntPtr) pos,
            out val
        );

        MltError.ThrowIfError(status);

        return val;
    }

    public static ulong VectorFLength(VectorFHandle handle)
    {
        UIntPtr length;
        MltStatus status = (MltStatus)MltNative.mltVectorFLength(handle, out length);
        MltError.ThrowIfError(status);

        return (ulong)length;
    }

    public static bool VectorFIsTransposed(VectorFHandle handle)
    {
        int isTransposed;
        MltStatus status = (MltStatus)MltNative.mltVectorFIsTransposed(handle, out isTransposed);
        MltError.ThrowIfError(status);

        if (isTransposed == 0)
            return false;

        return true;
    }

    public static void VectorFTranspose(VectorFHandle handle)
    {
        MltStatus status = (MltStatus)MltNative.mltVectorFTranspose(handle);
        MltError.ThrowIfError(status);
    }

    public static VectorFHandle VectorFAdd(VectorFHandle a, VectorFHandle b)
    {
        VectorFHandle c;
        MltStatus status = (MltStatus)MltNative.mltVectorFAdd(a, b, out c);
        MltError.ThrowIfError(status);

        return c;
    }

    public static void VectorFAddInPlace(VectorFHandle a, VectorFHandle b)
    {
        MltStatus status = (MltStatus)MltNative.mltVectorFAddInPlace(a, b);
        MltError.ThrowIfError(status);
    }

    public static VectorFHandle VectorFSubtract(VectorFHandle a, VectorFHandle b)
    {
        VectorFHandle c;
        MltStatus status = (MltStatus)MltNative.mltVectorFSubtract(a, b, out c);
        MltError.ThrowIfError(status);

        return c;
    }

    public static void VectorFSubtractInPlace(VectorFHandle a, VectorFHandle b)
    {
        MltStatus status = (MltStatus)MltNative.mltVectorFSubtractInPlace(a, b);
        MltError.ThrowIfError(status);
    }

    public static VectorFHandle VectorFMulScalar(VectorFHandle vec, float scalar)
    {
        VectorFHandle resVec;
        MltStatus status = (MltStatus)MltNative.mltVectorFMulScalar(vec, scalar, out resVec);
        MltError.ThrowIfError(status);

        return resVec;
    }

    public static void VectorFMulScalarInPlace(VectorFHandle vec, float scalar)
    {
        MltStatus status = (MltStatus)MltNative.mltVectorFMulScalarInPlace(vec, scalar);
        MltError.ThrowIfError(status);
    }

    public static float VectorFDot(VectorFHandle a, VectorFHandle b)
    {
        float val;
        MltStatus status = (MltStatus)MltNative.mltVectorFDot(a, b, out val);
        MltError.ThrowIfError(status);

        return val;
    }

    public static VectorFHandle VectorFHadamard(VectorFHandle a, VectorFHandle b)
    {
        VectorFHandle c;
        MltStatus status = (MltStatus)MltNative.mltVectorFHadamard(a, b, out c);
        MltError.ThrowIfError(status);

        return c;
    }

    public static VectorFHandle VectorFCopy(VectorFHandle handle)
    {
        VectorFHandle copyVec;
        MltStatus status = (MltStatus)MltNative.mltVectorFCopy(handle, out copyVec);
        MltError.ThrowIfError(status);

        return copyVec;
    }

    public static VectorFHandle VectorFClone(VectorFHandle handle)
    {
        VectorFHandle cloneVec;
        MltStatus status = (MltStatus)MltNative.mltVectorFClone(handle, out cloneVec);
        MltError.ThrowIfError(status);

        return cloneVec;
    }

    public static VectorFHandle VectorFSubvector(VectorFHandle handle, ulong pos, ulong len)
    {
        VectorFHandle subVec;
        MltStatus status = (MltStatus)MltNative.mltVectorFSubvector(handle, (UIntPtr)pos, (UIntPtr)len, out subVec);
        MltError.ThrowIfError(status);

        return subVec;
    }

    public static LinearRegressionHandle LinearRegressionCreate()
    {
        LinearRegressionHandle model;
        MltStatus status = (MltStatus)MltNative.mltLinearRegressionCreate(out model);
        MltError.ThrowIfError(status);

        return model;
    }

    public static float LinearRegressionPredict(LinearRegressionHandle model, VectorFHandle featureVec)
    {
        float val;
        MltStatus status = (MltStatus)MltNative.mltLinearRegressionPredict(model, featureVec, out val);
        MltError.ThrowIfError(status);

        return val;
    }

    public static void LinearRegressionFit(
            LinearRegressionHandle model,
            MatrixFHandle x,
            VectorFHandle y,
            float learningRate,
            ulong epoch
    )
    {
        MltStatus status = (MltStatus)MltNative.mltLinearRegressionFit(
            model,
            x,
            y,
            learningRate,
            (UIntPtr) epoch
        );

        MltError.ThrowIfError(status);
    }
}
