using MLTooling.Math;
using MLTooling.Models;
using MLTooling.Core;

class Programm
{
    static void matThing()
    {
        float[] buff1 = new float[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 , 14, 15, 16};
        float[] buff2 = new float[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 , 14, 15, 16};


        MatrixF mat = new MatrixF(buff1, 4,4);
        MatrixF mat2 = new MatrixF(buff2, 4,4);

        mat[0,3] = 5;

        Console.WriteLine(mat[0,3]);

        MatrixF mat3 = mat + mat2;
        Console.WriteLine(mat3[0,0]);
        Console.WriteLine(mat3[0,3]);

        Shape shape = mat.Shape;
        Console.WriteLine(shape);
    }

    static void vecThing()
    {
        float[] buff1 = new float[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 , 14, 15, 16};
        float[] buff2 = new float[] {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13 , 14, 15, 16};
    
        VectorF vec = new VectorF(buff1, (ulong)buff1.Length);
        VectorF vec2 =  new VectorF(buff2, (ulong)buff2.Length);
        VectorF emptyVec = new VectorF(5);

        emptyVec[3] = 3;
        Console.WriteLine(emptyVec[3]);

        VectorF vec3 = vec + vec2;
        Console.WriteLine(vec3[0]);
        Console.WriteLine(vec3[3]);

        Console.WriteLine(vec.IsTransposed);
        vec.Transpose();
        Console.WriteLine(vec.IsTransposed);
        Console.WriteLine(vec.Length);
    }

    static void LinearRegressionThing()
    {
        float[] xData = {0, 1, 2, 3, 4};
        float[] yData = {-14, -7, 0, 7, 14};    
        
        MatrixF X = new MatrixF(xData, 5, 1);
        VectorF y = new VectorF(yData, 5);

        float lr = 0.1f;
        ulong epochs = 500;
        LinearRegression model = new LinearRegression();
        model.Fit(X, y, lr, epochs);

        VectorF featPred = new VectorF(1);
        featPred[0] = 20f;
        float prediction = model.Predict(featPred);

        Console.WriteLine($"Prediction: {prediction}");
    }


    static void Main()
    {
        matThing();
        vecThing();
        LinearRegressionThing();

        Console.WriteLine("Hello world");
    }
}
