cmake_minimum_required(VERSION 3.28)
project(MLTooling VERSION 0.1.0 LANGUAGES C CXX)



set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_SCAN_FOR_MODULES ON)

add_library(MLTooling   
    "src/api/math/Matrix.cpp"
    "src/api/math/Vector.cpp"
    "src/api/models/LinearRegression.cpp"
    "src/data/DataColumn.cpp"
    "test/data/DataFrame.cpp"
    "src/math/matrix.cpp"
    "src/math/kernels/matrixkernels.cpp"
    "src/math/backend/cpu/tensorkernels.cpp"
    "src/compute/core/Storage.cpp"
    "src/compute/core/MltArray.cpp"
    "src/compute/backend/cpu/native.cpp"
    "src/compute/ops/ops.cpp"
)

target_sources(MLTooling
    PUBLIC
        FILE_SET CXX_MODULES FILES
            "modules/Error.cppm"
    PRIVATE
        FILE_SET internal_modules TYPE CXX_MODULES FILES
            "modules/Storage.cppm"
)

target_compile_options(MLTooling PRIVATE -fPIC)

target_include_directories(MLTooling
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include/public
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include/internal
)

install(TARGETS MLTooling DESTINATION lib)
install(DIRECTORY include/public DESTINATION include)

add_executable(example_basic examples/example_basic.cpp
)
target_link_libraries(example_basic PRIVATE MLTooling)

target_compile_options(MLTooling PRIVATE
    "$<$<CONFIG:Release>:-march=native>"
    "$<$<CONFIG:Release>:-ffast-math>"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(MLTooling PRIVATE
        "$<$<CONFIG:Release>:-fopt-info-vec>"
        "$<$<CONFIG:Release>:-fopt-info-vec-missed>"
    )
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_compile_options(MLTooling PRIVATE
        "$<$<CONFIG:Release>:-Rpass=loop-vectorize>"
        "$<$<CONFIG:Release>:-Rpass-missed=loop-vectorize>"
    )
endif()

message(STATUS "CXX Compiler: ${CMAKE_CXX_COMPILER}")
message(STATUS "Compiler ID : ${CMAKE_CXX_COMPILER_ID}")
message(STATUS "Build Type  : ${CMAKE_BUILD_TYPE}")

add_library(MLTooling_internal INTERFACE)
target_include_directories(MLTooling_internal INTERFACE
    ${PROJECT_SOURCE_DIR}/include/internal
)

add_executable(tests
    "test/test.cpp"
    "test/data/DataFrameTest.cpp"
    "test/math/datastructures/MatrixFloatTest.cpp"
    "test/math/datastructures/MatrixTest.cpp"
    "test/math/datastructures/VectorTest.cpp"
    "test/math/kernels/matrixkernelTest.cpp"
    "test/compute/MltArrayTest.cpp"
    "test/compute/StorageTest.cpp"
    "test/compute/backend/cpu/NativeTest.cpp"
)

target_link_libraries(tests PRIVATE MLTooling MLTooling_internal)

add_subdirectory(cwrapper)

#install(TARGETS MLToolingCapi DESTINATION lib)

## Kopieren ins Python-Paket-Verzeichnis nach dem Build
#add_custom_command(TARGET MLTooling_capi POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory
#        ${CMAKE_CURRENT_SOURCE_DIR}/pymltooling/_lib
#        COMMAND ${CMAKE_COMMAND} -E copy
#        $<TARGET_FILE:MLTooling_capi>
#        ${CMAKE_CURRENT_SOURCE_DIR}/pymltooling/_lib
#)
