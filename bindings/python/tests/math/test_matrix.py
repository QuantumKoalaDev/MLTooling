import unittest
from array import array

from MLTooling import Matrix
from MLTooling.core import Shape

class TestMat(unittest.TestCase):
    def test_creation(self):
        rows = 2
        cols = 3

        mat = Matrix(rows, cols)
        shape = mat.shape()

        self.assertEqual(shape.rows, rows)
        self.assertEqual(shape.cols, cols)

        mat_double = Matrix(rows, cols)
        shape = mat_double.shape()

        self.assertEqual(shape.rows, rows)
        self.assertEqual(shape.cols, cols)

    def test_creation_from_buffer(self):
        rows = 2
        cols = 3
        data = array("f", [1, 2, 3, 4, 5, 6])
        mat = Matrix.from_buffer(rows, cols, data)

        shape = mat.shape()
        self.assertEqual(rows, shape.rows)
        self.assertEqual(cols, shape.cols)

        self.assertEqual(mat[0,0], data[0])
        self.assertEqual(mat[0,1], data[2])
        self.assertEqual(mat[1,2], data[5])

        data_double = array("d", [1, 2, 3, 4, 5, 6])
        mat_double = Matrix.from_buffer(rows, cols, data_double)

        shape = mat_double.shape()
        self.assertEqual(rows, shape.rows)
        self.assertEqual(cols, shape.cols)

        self.assertEqual(mat_double[0,0], data_double[0])
        self.assertEqual(mat_double[0,1], data_double[2])
        self.assertEqual(mat_double[1,2], data_double[5])
    
    def test_shape(self):
        rows = 3
        cols = 2
        mat = Matrix(rows, cols)

        shape = mat.shape()

        self.assertEqual(shape.rows, rows)
        self.assertEqual(shape.cols, cols)

        mat_double = Matrix(rows, cols)

        shape_double = mat_double.shape()

        self.assertEqual(shape_double.rows, rows)
        self.assertEqual(shape_double.cols, cols)


    def test_matrix_addition(self):
        data_one = array("f", [1, 2, 3, 4, 5, 6])
        data_two = array("f", [7, 8, 9, 10, 11, 12])

        mat_one = Matrix.from_buffer(2, 3, data_one)
        mat_two = Matrix.from_buffer(2, 3, data_two)

        mat_result = mat_one + mat_two

        self.assertEqual(mat_result[0,0], data_one[0] + data_two[0])
        self.assertEqual(mat_result[0,1], data_one[2] + data_two[2])
        self.assertEqual(mat_result[1,2], data_one[5] + data_two[5])

    def test_matrix_addtion_in_place(self):
        data_one = array("f", [1, 2, 3, 4, 5, 6])
        data_two = array("f", [7, 8, 9, 10, 11, 12])

        mat_one = Matrix.from_buffer(2, 3, data_one)
        mat_two = Matrix.from_buffer(2, 3, data_two)

        mat_one += mat_two

        self.assertEqual(mat_one[0,0], data_one[0] + data_two[0])
        self.assertEqual(mat_one[0,1], data_one[2] + data_two[2])
        self.assertEqual(mat_one[1,2], data_one[5] + data_two[5])

    def test_matrix_multiplication(self):
        rows = 2
        cols = 3

        data_one = array("f", [1, 2, 3, 4, 5, 6])
        data_two = array("f", [7, 8, 9, 10, 11, 12])
        data_result = array("f", [76, 103, 100, 136])

        mat_one = Matrix.from_buffer(rows, cols, data_one)
        mat_two = Matrix.from_buffer(cols, rows, data_two)

        mat_result = mat_one * mat_two

        self.assertEqual(mat_result[0,0], data_result[0])
        self.assertEqual(mat_result[0,1], data_result[1])
        self.assertEqual(mat_result[1,1], data_result[3])

    def test_matrix_clone(self):
        data = array("f", [1, 2, 3, 4, 5, 6])
        mat = Matrix.from_buffer(2, 3, data)
        cloned_mat = mat.clone()

        self.assertEqual(cloned_mat[0,0], mat[0,0])
        self.assertEqual(cloned_mat[1,1], mat[1,1])
        self.assertEqual(cloned_mat[1,2], mat[1,2])

        cloned_mat[0,0] = 333

        self.assertNotEqual(cloned_mat[0,0], mat[0,0])

    def test_matrix_copy(self):
        data = array("f", [1, 2, 3, 4, 5, 6])
        mat = Matrix.from_buffer(2, 3, data)
        copied_mat = mat.copy()

        self.assertEqual(copied_mat[0,0], mat[0,0])
        self.assertEqual(copied_mat[1,1], mat[1,1])
        self.assertEqual(copied_mat[1,2], mat[1,2])

        val = 333
        copied_mat[0,0] = val

        self.assertEqual(copied_mat[0,0], val)
        self.assertEqual(copied_mat[0,0], mat[0,0])

    def test_submatrix(self):
        data = array("f", [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15])
        sub_mat_data = array("f", [7, 8, 9, 12, 13, 14])
        
        mat = Matrix.from_buffer(5, 3, data)
        sub_mat = mat.submatrix(Shape(1,1), Shape(3, 2))

        self.assertEqual(sub_mat[0,0], sub_mat_data[0])
        self.assertEqual(sub_mat[1,1], sub_mat_data[4])
        self.assertEqual(sub_mat[2,1], sub_mat_data[5])
