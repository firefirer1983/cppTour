set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(test_what class)

set(SOURCE class.cpp)

add_executable(
	class
	${SOURCE}
)

target_link_libraries(
	class
	gtest
)

