add_library(MLToolingCwrapper SHARED
    src/math/matrix.cpp
)

target_link_libraries(MLToolingCwrapper PRIVATE MLTooling)

target_include_directories(MLToolingCwrapper
    PUBLIC
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    PRIVATE
        ${PROJECT_SOURCE_DIR}/include
)

set_target_properties(MLToolingCwrapper PROPERTIES
    POSITION_INDEPENDENT_CODE ON
    CXX_STANDARD 23
    CXX_VISIBILITY_PRESET hidden
    VISIBILITY_INLINES_HIDDEN YES
)

if (WIN32)
    target_compile_definitions(MLToolingCwrapper PRIVATE MLTOOLING_CWRAPPER_EXPORTS)
endif()

add_executable(ctest
    test/math/matrixTest.c
)

target_link_libraries(ctest PRIVATE MLToolingCwrapper)
target_include_directories(ctest PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

