set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(test_what array_pointer)

set(SOURCE array_pointer.cpp)

add_executable(
		array_pointer
		${SOURCE}
)

target_link_libraries(
		array_pointer
		gtest
)

