cmake_minimum_required(VERSION 3.15)
project(MLTooling VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

add_library(MLTooling
    "include/Shape.h" 
    "include/Mat.h" 
    "src/Mat.cpp" 
    "include/Models/LinearRegressionModel.h" 
    "src/Models/LinearRegressionModel.cpp"
 "include/MLTooling.h")

target_compile_options(MLTooling PRIVATE -fPIC)

target_include_directories(MLTooling
    PUBLIC
        ${PROJECT_SOURCE_DIR}/include
)

install(TARGETS MLTooling DESTINATION lib)
install(DIRECTORY include/ DESTINATION include)

add_executable(example_basic examples/example_basic.cpp)
target_link_libraries(example_basic PRIVATE MLTooling)

add_library(MLToolingCabi SHARED
 "bindings/c/include/MLToolingCapi.h" "bindings/c/include/Models/LinearRegression.h" "bindings/c/src/LinearRegression.cpp")

target_link_libraries(MLToolingCabi PRIVATE MLTooling)

target_include_directories(MLToolingCabi
        PUBLIC ${PROJECT_SOURCE_DIR}/include
        PUBLIC ${PROJECT_SOURCE_DIR}/bindings/c/include)

if (WIN32)
    target_compile_definitions(MLToolingCabi PRIVATE MLTOOLING_CAPI_EXPORTS)
endif()
# PIC für Shared Library
set_target_properties(MLToolingCabi PROPERTIES POSITION_INDEPENDENT_CODE ON)
set_target_properties(MLToolingCabi PROPERTIES CXX_STANDARD 20)

#install(TARGETS MLToolingCabi DESTINATION lib)

## Kopieren ins Python-Paket-Verzeichnis nach dem Build
#add_custom_command(TARGET MLTooling_capi POST_BUILD
#        COMMAND ${CMAKE_COMMAND} -E make_directory
#        ${CMAKE_CURRENT_SOURCE_DIR}/pymltooling/_lib
#        COMMAND ${CMAKE_COMMAND} -E copy
#        $<TARGET_FILE:MLTooling_capi>
#        ${CMAKE_CURRENT_SOURCE_DIR}/pymltooling/_lib
#)
