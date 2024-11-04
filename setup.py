import os
import platform
from glob import glob
from setuptools import setup
from distutils.sysconfig import get_python_inc
from pybind11.setup_helpers import Pybind11Extension, build_ext

__version__ = "1.0.0"

include_dirs = [get_python_inc(), 'extern/pybind11/include', 'src/SealPIR/SEAL/native/src',
                'src/SealPIR/SEAL/build/native/src', 'src/SealPIR/src', 'src/SealPIR/build/src']

extra_objects_seal      = sorted(glob('src/SealPIR/SEAL/build/lib/*.lib') if platform.system() == "Windows" else glob('src/SealPIR/SEAL/build/lib/*.a'))
extra_objects_sealpir   = sorted(glob('src/SealPIR/src/*.a'))
extra_objects           = []

for file in extra_objects_seal:
    extra_objects.append(file)
for file in extra_objects_sealpir:
    extra_objects.append(file)

cpp_args = ['/std:c++latest'] if platform.system() == "Windows" else ['-std=c++17']

if len(extra_objects) < 1 or not os.path.exists(extra_objects[0]):
    print('Not found the seal lib file, check the `src/SealPIR/SEAL/build/lib`')
    exit(0)

ext_modules = [
    Pybind11Extension(
        "sealpir",
        sorted(glob('src/*.cpp')),
        include_dirs=include_dirs,
        extra_compile_args=cpp_args,
        extra_objects=extra_objects,
        define_macros = [('VERSION_INFO', __version__)],
    ),
]

setup(
    name="sealpir",
    version=__version__,
    description="Python wrapper for the Microsoft SEAL-PIR",
    ext_modules=ext_modules,
    cmdclass={"build_ext": build_ext},
    zip_safe=False,
    license='MIT',
    python_requires=">=3.6",
)
