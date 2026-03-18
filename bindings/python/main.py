from MLTooling import Matrix

from array import array

def main():
    mat1 = Matrix(1,2)

    data = array("f", [1, 2, 3, 4, 5, 6])
    mat2 = Matrix.from_buffer(2, 3, data)
    value = mat2[0,1]


    mat2[0,0] = 5
    setterValue = mat2[0,0]

    print(value, setterValue)

    shape =  mat2.shape()
    print(shape)

    mat3 = mat1 + mat2

main()