import unittest
import sys
import pathlib

sys.path.append(str(pathlib.Path(__file__).parent.parent.resolve()))

from pyMLTooling.container import Mat
from pyMLTooling.error import MltNullPtrError, MltOutOfRangeError

class TestMat(unittest.TestCase):
        def test_creation_and_shape(self):
            mat = Mat(rows=2, cols=2)
            shape = mat.get_shape()
            self.assertEqual(shape.rows, 2)
            self.assertEqual(shape.cols, 2)
        
        def test_creation_from_flat_array(self):
             data = [1.0, 2.0, 3.0, 4.0]
             mat = Mat.from_flat_array(2, 2, data)
             shape = mat.get_shape()

             self.assertEqual(shape.rows, 2)
             self.assertEqual(shape.cols, 2)
             self.assertEqual(mat[1,1], 4.0)

        def test_get_set_item(self):
            mat = Mat(2, 2)
            mat[0, 1] = 5.5
            self.assertEqual(mat[0, 1], 5.5)

        def test_iteration(self):
            mat = Mat(2, 2)
            rows = list(mat)
            self.assertEqual(rows, [[0.0, 0.0], [0.0, 0.0]])

        def test_append_row(self):
             mat = Mat(2, 2)
             row = [1.0, 2.0]
             mat.append_row(row)

             self.assertEqual(mat[2, 0], 1.0)
             self.assertEqual(mat[2, 1], 2.0)

        def test_invalid_index(self):
            mat = Mat(2, 2)

            with self.assertRaises(MltOutOfRangeError):
                 mat[5, 0]

            with self.assertRaises(MltNullPtrError):
                  mat._ptr = None # type: ignore[reportPrivateUsage]
                  mat.get_row(0)            

if __name__ == "__main__":
     unittest.main()
