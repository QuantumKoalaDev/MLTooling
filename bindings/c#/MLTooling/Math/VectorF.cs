using System.Runtime.InteropServices;

using MLTooling.Bindings;
using MLTooling.Core;
using MLTooling.Core.Handles;

namespace MLTooling.Math;

public sealed class VectorF
{
    internal VectorFHandle Handle {get; }

    public SafeHandle DangerousHandle => Handle;
    public ulong Length => getLength();
    public bool IsTransposed => getTransposed();

    public VectorF(ulong size)
    {
        Handle = MltWrapper.VectorFCreate(size);
    }

    public VectorF(float[] data, ulong size)
    {
        Handle = MltWrapper.VectorFCreateFromBuff(data, size);
    }

    public float this[ulong pos]
    {
        get => MltWrapper.VectorFGet(this.Handle, pos);
        set => MltWrapper.VectorFSet(this.Handle, pos, value);
    }

    public void Transpose()
    {
        MltWrapper.VectorFTranspose(this.Handle);
    }

    public VectorF Add(VectorF other)
    {
        VectorFHandle resultHandle = MltWrapper.VectorFAdd(this.Handle, other.Handle);

        return new VectorF(resultHandle);
    }

    public void AddInPlace(VectorF other)
    {
        MltWrapper.VectorFAddInPlace(this.Handle, other.Handle);
    }

    public VectorF Subtract(VectorF other)
    {
        VectorFHandle resultHandle = MltWrapper.VectorFSubtract(this.Handle, other.Handle);

        return new VectorF(resultHandle);
    }

    public void SubtractInPlace(VectorF other)
    {
        MltWrapper.VectorFSubtractInPlace(this.Handle, other.Handle);
    }

    public VectorF MulScalar(float scalar)
    {
        VectorFHandle resultHandle = MltWrapper.VectorFMulScalar(this.Handle, scalar);

        return new VectorF(resultHandle);
    }

    public void MulScalarInPlace(float scalar)
    {
        MltWrapper.VectorFMulScalarInPlace(this.Handle, scalar);
    }

    public float Dot(VectorF other)
    {
        return MltWrapper.VectorFDot(this.Handle, other.Handle);
    }

    public VectorF Hadamard(VectorF other)
    {
        VectorFHandle resultHandle = MltWrapper.VectorFHadamard(this.Handle, other.Handle);

        return new VectorF(resultHandle);
    }

    public VectorF Copy()
    {
        VectorFHandle resultHandle = MltWrapper.VectorFCopy(this.Handle);

        return new VectorF(resultHandle);
    }

    public VectorF Clone()
    {
        VectorFHandle resultHandle = MltWrapper.VectorFClone(this.Handle);

        return new VectorF(resultHandle);
    }

    public VectorF Subvector(ulong pos, ulong length)
    {
        VectorFHandle resultHandle = MltWrapper.VectorFSubvector(this.Handle, pos, length);

        return new VectorF(resultHandle);
    }

    public static VectorF operator +(VectorF a, VectorF b)
    {
        return a.Add(b);
    }
    


    private VectorF(VectorFHandle handle)
    {
        Handle = handle;
    }

    private ulong getLength()
    {
        return MltWrapper.VectorFLength(Handle);
    }

    private bool getTransposed()
    {
        return MltWrapper.VectorFIsTransposed(Handle);
    }
}
