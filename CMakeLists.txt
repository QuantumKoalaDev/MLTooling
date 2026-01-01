cmake_minimum_required(VERSION 3.15)
project(MLTooling VERSION 0.1.0 LANGUAGES C CXX)



set(CMAKE_CXX_STANDARD 23)

add_library(MLTooling   
    "src/Container/Mat.cpp" 
    "src/Models/LinearRegressionModel.cpp"
    "src/data/DataColumn.cpp"
)

target_compile_options(MLTooling PRIVATE -fPIC)

target_include_directories(MLTooling
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

install(TARGETS MLTooling DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

add_executable(example_basic examples/example_basic.cpp)
target_link_libraries(example_basic PRIVATE MLTooling)

add_executable(tests
    "test/test.cpp"
    "test/math/tensor/MatrixTest.cpp"
    "test/data/DataFrameTest.cpp"
)
target_link_libraries(tests PRIVATE MLTooling)

add_subdirectory(bindings/c)

#install(TARGETS MLToolingCapi DESTINATION lib)

## Kopieren ins Python-Paket-Verzeichnis nach dem Build
#add_custom_command(TARGET MLTooling_capi POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory
#        ${CMAKE_CURRENT_SOURCE_DIR}/pymltooling/_lib
#        COMMAND ${CMAKE_COMMAND} -E copy
#        $<TARGET_FILE:MLTooling_capi>
#        ${CMAKE_CURRENT_SOURCE_DIR}/pymltooling/_lib
#)
