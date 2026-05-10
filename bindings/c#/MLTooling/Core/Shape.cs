namespace MLTooling.Core;

public struct Shape
{
    ulong Rows;
    ulong Cols;

    public Shape(ulong rows, ulong cols)
    {
        Rows = rows;
        Cols = cols;
    }

    public override string ToString()
    {
        return $"Shape(Rows={Rows}, Cols={Cols})";
    }

}
