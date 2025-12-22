# Build

Linux:
```
cmake ..
make -j
```

Windows:
```
cmake .. -G "Visual Studio 18 2026"
cmake --build . --config Release
```

For Python bindings, the generated dynamic library (.so/.dll) must be copied to pyMLTooling/_lib.
Consider adding a post-build step or script to automate this.


# Coding Conventions

- **Python**
  - Each binding instance owns its own copy; sharing references is not allowed.
  - Tests should be written using the `unittest` module.
  - Python class interacting with the C-wrapper are owning. Therefore the implementation of copy has to be
	explicitly marked as "Not implemented".
  - C++ structs should be implemented as dataclasses as they do not have any related functionality.
  - Python code must use strict type checking (Pylance).

- **C++**
  - Follow the existing project structure.
  - Use Allman brace style, with some project-specific rules if needed.
  - Each class must be defined in a separate file.
  - Use `.hpp` for C++ headers; `.h` is reserved for C headers for clarity.
  - `src` and `include` directories must have identical folder structures.
  - Use structs only for plain data without related functionality.

- **C**
  - Use K&R brace style.
  - Custom rules may apply for certain use cases.
  - For functions tied to C++ objects the following naming convention applies:
	- `mat_[C++ namespace shortend to two letters]_[C++ class name]_[function description]`
  - All functions must start with mt_* (except for test functions).


# Testing

- **Python**
  - Navigate to `bindings/python/tests`
  - Run: `python container_test.py`
  - If the dynamic library cannot be found, see the Python bindings section in Build.

- **C++**
  - The project must be built first.
  - Test exectuables are located in the `out` folder in the project root.

- **C**
  - The project must be build first.
  - Test executables are located in the `out` folder in the project root. (`ctest`)
