cmake_minimum_required(VERSION 3.12.4)

project(ip_filter LANGUAGES C CXX)

set(src
	${PROJECT_SOURCE_DIR}/main.cpp 
	${PROJECT_SOURCE_DIR}/ip_filter.cpp)

add_executable(ip_filter_run ${src})
if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
    target_link_libraries(ip_filter_run PRIVATE "-lc++fs")
endif()

if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_link_libraries(ip_filter_run PRIVATE "-lstdc++fs")
endif()

#test: ip_filter
add_executable(test_ip_filter_run ${PROJECT_SOURCE_DIR}/test_ip_filter.cpp ${PROJECT_SOURCE_DIR}/ip_filter.cpp)
set_target_properties(test_ip_filter_run 
    PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
)
target_link_libraries(test_ip_filter_run
    ${Boost_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
    PRIVATE "-lstdc++fs"
)

if(CMAKE_BUILD_TYPE EQUAL "RELEASE")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
else()
    # cmake .. -DCMAKE_BUILD_TYPE=DEBUG
    set(CMAKE_BUILD_TYPE "DEBUG")
    set_target_properties(
    	ip_filter_run
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-g;-O0;-Wall;-Wextra;-Werror;-Wpedantic;")

    target_link_libraries(ip_filter_run PRIVATE -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer)
endif()

#tests
enable_testing()
add_test(NAME test_ip_filter COMMAND test_ip_filter_run)