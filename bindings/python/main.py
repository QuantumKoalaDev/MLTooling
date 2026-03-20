from MLTooling import Dtypes
from MLTooling.core.dtypes import typecode_to_dtype

from array import array

def main():
    arr_float = array("f", [1])
    arr_double = array("d", [1])

    print(arr_float.typecode)
    print(arr_double.typecode)

    print(typecode_to_dtype(arr_float))
    

main()