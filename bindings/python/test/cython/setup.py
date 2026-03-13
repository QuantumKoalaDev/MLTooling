from setuptools import setup, Extension
from Cython.Build import cythonize
import os

wrapper_include = os.path.abspath("../../../cwrapper/include/mlt")
wrapper_lib_dir = os.path.abspath("../../../build/cwrapper")

ext_modules = [
Extension(
    "Matrix",
    sources=["Matrix.pyx"],
    language="c",
    include_dirs=[wrapper_include],
    library_dirs=[wrapper_lib_dir],
    libraries=["MLToolingCwrapper"],
    extra_compile_args=["-std=c17"],
    extra_link_args=["-Wl,-rpath,$ORIGIN"]
)
]

setup(
    name="Matrix",
    ext_modules=cythonize(ext_modules)
)
