from pyMLTooling.model import LinearRegressionModel
from pyMLTooling.container import Mat

def main():
    flat_data = [
        1.0, 2.0, 3.0,
        4.0, 5.0, 6.0,
        7.0, 8.0, 9.0
    ]

    rows = 3
    cols = 3

    # mat = Mat(flat_data, rows, cols)
    mat = Mat.from_flat_array(rows, cols, flat_data)

    shape = mat.get_shape()
    print("Shape:", shape.rows, "x", shape.cols)

    for i in range(shape.rows):
        row = mat.get_row(i)
        print(f"Row {i}:", row)

    y = [5.0, 7.0, 9.0]

    model = LinearRegressionModel()

    learning_rate = 0.01
    epochs = 10000
    model.fit(mat, y, learning_rate, epochs)

    new_sample = [4.0, 5.0]

    pred = model.predict(new_sample)
    print(f"Prediction for {new_sample}: {pred}")

def linear_regression_example1():
    # y = 7x - 14
    x_data = [
        0.0,
        1.0,
        2.0,
        3.0,
        4.0
    ]
    y_data = [-14.0, -7.0, 0.0, 7.0, 14.0]

    # Mat erzeugen: 5 Zeilen, 1 Spalte
    # mat = Mat(data=x_data, rows=5, cols=1)
    mat = Mat.from_flat_array(5, 1, x_data)

    # Modell erstellen
    model = LinearRegressionModel()

    learning_rate = 0.1
    epochs = 500

    # Trainieren
    model.fit(mat, y_data, learning_rate, epochs)

    # Vorhersage
    pred = model.predict([20.0])
    print(f"Prediction for [20]: {pred}")  # Sollte ~126 sein


if __name__ == "__main__":
    main()
    linear_regression_example1()
