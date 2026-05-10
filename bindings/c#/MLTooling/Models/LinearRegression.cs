using System.Runtime.InteropServices;

using MLTooling.Bindings;
using MLTooling.Core.Handles;
using MLTooling.Math;

namespace MLTooling.Models;

public sealed class LinearRegression
{
    internal LinearRegressionHandle Handle {get; }

    public SafeHandle DangerousHandle => Handle;


    public LinearRegression()
    {
        Handle = MltWrapper.LinearRegressionCreate();
    }

    public float Predict(VectorF features)
    {
        return MltWrapper.LinearRegressionPredict(this.Handle, features.Handle);
    }

    public void Fit(MatrixF x, VectorF y, float lr, ulong epochs)
    {
        MltWrapper.LinearRegressionFit(this.Handle, x.Handle, y.Handle, lr, epochs);
    }
}
