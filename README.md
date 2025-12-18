# Build

Linux:
```
cmake ..
make -j
```

Windows:
```
cmake .. -G "Visual Studio 18 2026" \
cmake --build . --config Release
```

For Python bindings, the generated dynamic library (.so/.dll) must be copied to pyMLTooling/_lib.
Consider adding a post-build step or script to automate this.


# Coding Conventions

- **Python**
  - Each binding instance owns its own copy; sharing references is not allowed.
  - Tests should be written using the `unittest` module.

- **C++**
  - Follow the existing project structure.
  - Use Allman brace style, with some project-specific rules if needed.
  - Each class must be defined in a separate file.
  - Use `.hpp` for C++ headers; `.h` is reserved for C headers for clarity.
  - `src` and `include` directories must have identical folder structures.

- **C**
  - Use K&R brace style.
  - Custom rules may apply for certain use cases.