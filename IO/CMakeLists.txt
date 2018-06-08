set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(test_what type_length)

set(SOURCE type_length.cpp)

add_executable(
	type_length
	${SOURCE}
)

target_link_libraries(
	type_length
	gtest
)

