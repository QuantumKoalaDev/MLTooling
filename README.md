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
