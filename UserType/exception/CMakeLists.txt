set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(test_what exception)

set(SOURCE exception.cpp)

add_executable(
	exception
	${SOURCE}
)

target_link_libraries(
	exception
	gtest
)

