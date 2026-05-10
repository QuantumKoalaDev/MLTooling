using Microsoft.Win32.SafeHandles;
using MLTooling.Bindings;


namespace MLTooling.Core.Handles;

abstract class NativeHandle : SafeHandleZeroOrMinusOneIsInvalid
{
    public NativeHandle() : base(true)
    {}
}

internal sealed class MatrixFHandle : NativeHandle
{
    public MatrixFHandle()
    {}

    protected override bool ReleaseHandle()
    {
        MltNative.mltFwMatrixFDestroy(handle);

        return true;
    }
}

internal sealed class VectorFHandle : NativeHandle
{
    public VectorFHandle()
    {}

    protected override bool ReleaseHandle()
    {
        MltNative.mltVectorFDestroy(handle);    

        return true;
    }
}

internal sealed class LinearRegressionHandle : NativeHandle
{
    public LinearRegressionHandle()
    {}

    protected override bool ReleaseHandle()
    {
        MltNative.mltLinearRegressionDestroy(handle);

        return true;
    }
}
