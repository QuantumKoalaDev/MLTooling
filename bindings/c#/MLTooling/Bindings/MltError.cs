namespace MLTooling.Bindings;

internal static class MltError
{
    public static void ThrowIfError(MltStatus status)
    {
        if (status == MltStatus.SUCCESS)
            return;

        throw CreateException(status);
    }

    private static Exception CreateException(MltStatus status)
    {
        return status switch
        {
            MltStatus.NULL_PTR => new NullReferenceException("Native NULL pointer"),
            MltStatus.OUT_OF_BOUNDS => new IndexOutOfRangeException(""),
            MltStatus.ALLOCATION_FAILED => new OutOfMemoryException(),
            MltStatus.SHAPE_MISSMATCH => new InvalidOperationException("Shape missmatch"),
            _ => new InvalidOperationException($"Unknown native error: {status}")
        };
    }
}
