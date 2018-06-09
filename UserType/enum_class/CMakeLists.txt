set(CMAKE_CXX_FLAGS "-Wall -std=gnu++11 -g -O0 -pthread")
set(googleTestDir ../../googletest)
include_directories(${googleTestDir}/googletest/include)

set(test_what enum_class)

set(SOURCE enum_class.cpp)

add_executable(
	enum_class
	${SOURCE}
)

target_link_libraries(
	enum_class
	gtest
)

