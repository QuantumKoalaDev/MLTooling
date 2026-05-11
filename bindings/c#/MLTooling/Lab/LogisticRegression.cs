using MLTooling.Core;
using MLTooling.Math;

namespace MLTooling.Lab;

public sealed class LogisticRegression
{
    public float LearningRate {get;}
    public ulong Epochs {get;}

    private VectorF _weights;
    private float _bias;


    LogisticRegression(float learningRate, ulong epochs)
    {
        LearningRate = learningRate;
        Epochs = epochs;

        _weights = new VectorF(0);
        _bias = 0f;
    }

    void Fit(MatrixF X, VectorF y)
    {
        ulong nSamples, nFeatures = X.Shape.Cols;

        this._weights = new VectorF(nFeatures);
        this._bias = 0f;

        for (ulong i = 0; i <= this.Epochs; i++)
        {
            VectorF linearModel = new VectorF(nFeatures); // Hier muss eigentlich eine matrix-vector-multiplication hin (np.dot)
            VectorF yPred = sigmoidVec(linearModel);


            float dw = (1 / nSamples) *
        }
    }



    private void negVec(VectorF vec)
    {
        ulong num = vec.Length;

        for (ulong i = 0; i < num; i++)
            vec[i] = -vec[i];
    }

    private void expVec(VectorF vec)
    {
        ulong num = vec.Length;

        for (ulong i = 0; i < num; i++)
            vec[i] = (float)System.Math.Exp(vec[i]);
    }

    private void addScalarVec(VectorF vec, float scalar)
    {
        ulong num = vec.Length;

        for (ulong i = 0; i < num; i++)
            vec[i] += scalar;
    }

    private void divScalarVec(VectorF vec, float scalar)
    {
        ulong num = vec.Length;

        for (ulong i = 0; i < num; i++)
            vec[i] /= scalar;
    }

    private VectorF sigmoidVec(VectorF vec)
    {
        VectorF sigVec = vec.Clone();

        negVec(sigVec);
        expVec(sigVec);
        addScalarVec(sigVec, 1f);
        divScalarVec(sigVec, 1f);

        return sigVec;
    }
}

