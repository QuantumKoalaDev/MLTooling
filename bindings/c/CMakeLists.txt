add_library(MLToolingCapi SHARED
	"include/MLToolingCapi.h"
	"include/Models/LinearRegression.h"
	"src/Models/LinearRegression.cpp"
	"include/Container/Mat.h" 
	"src/Container/Mat.cpp"
)

target_link_libraries(MLToolingCapi PRIVATE MLTooling)

target_include_directories(MLToolingCapi
	PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/include
		${PROJECT_SOURCE_DIR}/include
)

set_target_properties(MLToolingCapi PROPERTIES
	POSITION_INDEPENDENT_CODE ON
	CXX_STANDARD 20)

if (WIN32)
	target_compile_definitions(MLToolingCapi PRIVATE MLTOOLING_CAPI_EXPORTS)
endif()

add_executable(ctest test/test.c)
target_link_libraries(ctest PRIVATE MLToolingCapi)
target_include_directories(ctest PRIVATE
    ${PROJECT_SOURCE_DIR}/bindings/c/include
    ${PROJECT_SOURCE_DIR}/include
)