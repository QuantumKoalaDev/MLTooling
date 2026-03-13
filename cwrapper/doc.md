## C API Naming & Design Conventions

This project provides a C wrapper for the C++ core of MLT.
The C API mirrors the original C++ class structure while remaining idiomatic and safe for C and FFI bindings.

### Goals

* Predictable naming
* Easy mapping from C++ classes
* Stable ABI
* Simple bindings for other languages

### Type Naming

C types follow this pattern:

```
mlt<Class><TypeSuffix>
```

**Examples:**

```
Matrix<float>   -> mltMatrixF
Matrix<double>  -> mltMatrixD
Vector<float>   -> mltVectorF
Vector<double>  -> mltVectorD
```

**Declarations:**

```c
typedef struct mltMatrixF mltMatrixF;
typedef struct mltMatrixD mltMatrixD;
```

All structs are opaque in the public API to keep the ABI stable. No additional typedefs or wrappers are needed in the C-bindings layer except for new types like `Shape`.

### Function Naming

**C-Wrapper functions:**

```
mltFw<Class><TypeSuffix><Verb>
```

`Fw` prevents collisions with higher-level C-bindings.

**Examples:**

```
mltFwMatrixFCreate
mltFwMatrixFDestroy
mltFwMatrixFMultiply
```

**Declarations:**

```c
mltStatus mltFwMatrixFCreate(size_t rows, size_t cols, mltMatrixF** out);
mltStatus mltFwMatrixFDestroy(mltMatrixF* matrix);
```

### Status Codes

```c
typedef enum {
    MLT_SUCCESS = 0,
    MLT_ERROR_INVALID_ARGUMENT,
    MLT_ERROR_OUT_OF_MEMORY,
    MLT_ERROR_INTERNAL
} mltStatus;
```

### Creation Pattern

Objects are created via output parameters.

```
mltFw<Class><TypeSuffix>Create
```

### Destruction Pattern

```
mltFw<Class><TypeSuffix>Destroy
```

**Example:**

```c
mltStatus mltFwDestroyMatrixF(mltMatrixF* matrix);
```

### Type Suffixes

```
F -> float
D -> double
```

**Examples:**

```
mltMatrixF
mltMatrixD
mltVectorF
```

### Design Goals

* Consistency across wrapped classes
* Stable ABI and language bindings
* Predictable API

### Tests

Each function should have a test in the `test` folder, following the `include/mlt` folder structure, using the provided custom test system.

