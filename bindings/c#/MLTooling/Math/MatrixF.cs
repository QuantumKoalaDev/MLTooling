using System.Runtime.InteropServices;

using MLTooling.Bindings;
using MLTooling.Core;
using MLTooling.Core.Handles;


namespace MLTooling.Math;


public sealed class MatrixF
{

    internal MatrixFHandle Handle { get; }

    public SafeHandle DangerousHandle => Handle;
    public Shape Shape => getShape();

    public MatrixF(ulong rows, ulong cols)
    {
        Handle = MltWrapper.MatrixFCreate(rows, cols);
    }

    public MatrixF(float[] data, ulong rows, ulong cols)
    {
        Handle = MltWrapper.MatrixFCreateFromBuff(data, rows, cols);
    }

    public float this[ulong row, ulong col]
    {
        get => MltWrapper.MatrixFGet(Handle, row, col);
        set => MltWrapper.MatrixFSet(Handle, row, col, value);
 
    }

    public MatrixF Add(MatrixF other)
    {
        MatrixFHandle resultHandle = MltWrapper.MatrixFAdd(this.Handle, other.Handle);

        return new MatrixF(resultHandle);
    }

    public void AddInPlace(MatrixF other)
    {
        MltWrapper.MatrixFAddInPlace(this.Handle, other.Handle);
    }

    public MatrixF Multiply(MatrixF other)
    {
        MatrixFHandle resultHandle = MltWrapper.MatrixFMultiply(this.Handle, other.Handle);

        return new MatrixF(resultHandle);
    }

    public MatrixF Copy()
    {
        MatrixFHandle resultHandle = MltWrapper.MatrixFCopy(this.Handle);

        return new MatrixF(resultHandle);
    }

    public MatrixF Clone()
    {
        MatrixFHandle resultHandle = MltWrapper.MatrixFClone(this.Handle);

        return new MatrixF(resultHandle);
    }

    public MatrixF Submatrix(ulong startRow, ulong startCol, ulong rowCount, ulong colCount)
    {
        MatrixFHandle resultHandle = MltWrapper.MatrixFSubmatrix(
            this.Handle,
            startRow,
            startCol,
            rowCount,
            colCount
        );

        return new MatrixF(resultHandle);
    }

    public static MatrixF operator +(MatrixF a, MatrixF b)
    {
        return a.Add(b);
    }

    public static MatrixF operator *(MatrixF a, MatrixF b)
    {
        return a.Multiply(b);
    }

    private MatrixF(MatrixFHandle handle)
    {
        Handle = handle;
    }

    private Shape getShape()
    {
        MltShape shape = MltWrapper.MatrixFGetShape(this.Handle);

        return new Shape(shape.rows, shape.cols);
    }
}
