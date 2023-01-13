# This file is enables building the libtiledbsoma external package as part of the
# tiledbsoma module install process.
#
# Local non-editable install:
#   `pip install .`
#
# Local editable install:
#   `pip install -e .`
#
# Install from PyPI
#   `pip install tiledbsoma`
#
# Based on ideas from https://github.com/pybind/cmake_example
# The `bld` script here is reused for pip install, CI, and local builds.

# type: ignore

import os
import shutil
import subprocess
import sys

from setuptools import Extension, find_packages, setup
from setuptools.command.bdist_egg import bdist_egg
from setuptools.command.build_ext import build_ext
from wheel.bdist_wheel import bdist_wheel

sys.path.insert(0, os.path.dirname(__file__))
import version  # noqa E402

MODULE_NAME = "tiledbsoma"
EXT_NAME = "tiledbsoma.libtiledbsoma"
TILEDBSOMA_DEBUG_BUILD = False
LIBTILEDBSOMA_PATH = None
DOWNLOAD_TILEDB_PREBUILT = True

LIBNAMES = ["libtiledbsoma.dylib", "libtiledbsoma.so", "libtiledbsoma.dll", "libtiledbsoma.a"]

args = sys.argv[:]
for arg in args:
    if arg.find("--debug") == 0:
        TILEDBSOMA_DEBUG_BUILD = True
        sys.argv.remove(arg)
    if arg.find("--libtiledbsoma") == 0:
        LIBTILEDBSOMA_PATH = arg.split("=")[1]
        sys.argv.remove(arg)
    if arg.find("--disable-download-tiledb-prebuilt") == 0:
        DOWNLOAD_TILEDB_PREBUILT = False
        sys.argv.remove(arg)


def find_or_build(setuptools_cmd, recursive=True):
    global LIBTILEDBSOMA_PATH
    # Setup paths
    python_dir = os.path.abspath(os.path.dirname(__file__))
    src_dir = f"{python_dir}/src/{MODULE_NAME}"
    lib = None
    if LIBTILEDBSOMA_PATH is not None:
        # system install
        pass
    elif os.path.islink(os.path.join(python_dir, "dist_links/scripts")):
        # in git source tree
        scripts_dir = f"{python_dir}/../../scripts"
        #lib_dirs = [f"{python_dir}/../../dist/lib"]
        LIBTILEDBSOMA_PATH = f"{python_dir}/../../dist"
    else:
        # in extracted sdist, with libtiledbsoma copied into dist_links/
        scripts_dir = f"{python_dir}/dist_links/scripts"
        #lib_dirs = [f"{python_dir}/dist_links/dist/lib"]
        LIBTILEDBSOMA_PATH = f"{python_dir}/dist_links/dist"

    lib_dirs = LIBTILEDBSOMA_PATH
    lib_dirs = [os.path.join(os.path.normpath(LIBTILEDBSOMA_PATH), "lib")]
    if sys.platform.startswith("linux"):
        lib_dirs += [
            os.path.join(LIBTILEDBSOMA_PATH, "lib64"),
            os.path.join(LIBTILEDBSOMA_PATH, "lib", "x86_64-linux-gnu"),
        ]
    elif os.name == "nt":
        lib_dirs += [os.path.join(LIBTILEDBSOMA_PATH, "bin")]
    inc_dir = [os.path.join(LIBTILEDBSOMA_PATH, "include")]
    if sys.platform == "darwin":
        LFLAGS += ["-Wl,-rpath,{}".format(p) for p in lib_dirs]

    # Call the build script if the install library directory does not exist
    found = False
    for lib_dir in lib_dirs:
        # Exit early so that we stick with the first found library, i.e we check shared before static.
        if found:
            break
        for libname in LIBNAMES:
            print(f"Checking: {os.path.join(lib_dir, libname)} exists: {os.path.exists(os.path.join(lib_dir, libname))}")
            if os.path.exists(os.path.join(lib_dir, libname)):
                lib = os.path.join(lib_dir, libname)
                found = True
                break

    if not found:
        print("Prebuilt libtiledbsoma not found, building from source")
        subprocess.run("bash bld", cwd=scripts_dir, shell=True, check=True)
        for lib_dir in lib_dirs:
            if found:
                break
            for libname in LIBNAMES:
                print(f"Checking2: {os.path.join(lib_dir, libname)} exists: {os.path.exists(os.path.join(lib_dir, libname))}")
                if os.path.exists(os.path.join(lib_dir, libname)):
                    lib = os.path.join(lib_dir, libname)
                    found = True
                    break
        if not found:
            raise Exception("Couldn't find libtiledbsoma")

    # Copy native libs into the package dir so they can be found by package_data
    package_data = []
    #for obj in [os.path.join(lib_dirs, f) for f in os.listdir(lib_dirs)]:
        # skip static library
    if not lib.endswith(".a"):
        print(f"  copying file {lib} to {src_dir}")
        shutil.copy(lib, src_dir)
        package_data.append(os.path.basename(lib))

    # Install shared libraries inside the Python module via package_data.
    print(f"  adding to package_data: {package_data}")
    setuptools_cmd.distribution.package_data.update({MODULE_NAME: package_data})


def get_ext_modules():
    return [CMakeExtension(EXT_NAME)]


class CMakeExtension(Extension):
    def __init__(self, name):
        Extension.__init__(self, name, sources=[])


class BuildExtCmd(build_ext):
    def run(self):
        find_or_build(self)


class BdistEggCmd(bdist_egg):
    def run(self):
        find_or_build(self)
        bdist_egg.run(self)


class BdistWheelCmd(bdist_wheel):
    def run(self):
        find_or_build(self)
        bdist_wheel.run(self)


if __name__ == "__main__":
    setup(
        name=MODULE_NAME,
        description="Python API for efficient storage and retrieval of single-cell data using TileDB",
        author="TileDB, Inc.",
        author_email="help@tiledb.io",
        maintainer="TileDB, Inc.",
        maintainer_email="help@tiledb.io",
        url="https://github.com/single-cell-data/TileDB-SOMA/apis/python",
        license="MIT",
        classifiers=[
            "Intended Audience :: Developers",
            "Intended Audience :: Information Technology",
            "Intended Audience :: Science/Research",
            "License :: OSI Approved :: MIT License",
            "Programming Language :: Python",
            "Topic :: Scientific/Engineering :: Bio-Informatics",
            "Operating System :: Unix",
            "Operating System :: POSIX :: Linux",
            "Operating System :: MacOS :: MacOS X",
            "Programming Language :: Python :: 3.7",
            "Programming Language :: Python :: 3.8",
            "Programming Language :: Python :: 3.9",
        ],
        package_dir={"": "src"},
        packages=find_packages("src"),
        zip_safe=False,
        install_requires=[
            "anndata",
            "numpy",
            "pandas",
            "pyarrow",
            "scanpy",
            "scipy",
            "tiledb>=0.19.0",
            "typing-extensions",  # Note "-" even though `import typing_extensions`
        ],
        python_requires=">=3.7",
        ext_modules=get_ext_modules(),
        cmdclass={
            "build_ext": BuildExtCmd,
            "bdist_egg": BdistEggCmd,
            "bdist_wheel": BdistWheelCmd,
        },
        version=version.getVersion(),
    )
