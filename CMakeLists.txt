cmake_minimum_required(VERSION 3.15)
project(MLTooling VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(MLTooling   
    "src/data/DataColumn.cpp"
    "test/data/DataFrame.cpp"
    "src/math/datastructures/matrix.cpp"
    "src/math/datastructures/Matrix.cpp"
    "src/math/kernels/matrixkernels.cpp"
    "src/math/datastructures/Vector.cpp"
    "src/models/LinearRegression.cpp"
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
