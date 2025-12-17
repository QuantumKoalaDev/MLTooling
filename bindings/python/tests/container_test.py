import unittest
import sys
import pathlib

sys.path.append(str(pathlib.Path(__file__).parent.parent.resolve()))

from pyMLTooling.container import Mat

class TestMat(unittest.TestCase):
        def test_creation_and_shape(self):
            data = [1.0, 2.0, 3.0, 4.0]
            mat = Mat(data, rows=2, cols=2)
            shape = mat.get_shape()
            self.assertEqual(shape.rows, 2)
            self.assertEqual(shape.cols, 2)

        def test_get_set_item(self):
            data = [0.0, 0.0, 0.0, 0.0]
            mat = Mat(data, 2, 2)
            mat[0, 1] = 5.5
            self.assertEqual(mat[0, 1], 5.5)

        def test_iteration(self):
            data = [1.0, 2.0, 3.0, 4.0]
            mat = Mat(data, 2, 2)
            rows = list(mat)
            self.assertEqual(rows, [[1.0, 2.0], [3.0, 4.0]]) 

if __name__ == "__main__":
     unittest.main()
