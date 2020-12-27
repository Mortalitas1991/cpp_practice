cmake_minimum_required(VERSION 3.13.4)

project(cpp_practice VERSION 0.0.0$ENV{TRAVIS_BUILD_NUMBER} LANGUAGES C CXX)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
# export BOOST_ROOT=/usr/local/${VERSION}
include_directories(${Boost_INCLUDE_DIRS})

#version
#configure_file(version.h.in ${PROJECT_SOURCE_DIR}/version.h)

#main
add_executable(program_run ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/version.cpp)
add_library(version ${PROJECT_SOURCE_DIR}/version.cpp)

#ip filter
add_executable(ip_filter_run ${PROJECT_SOURCE_DIR}/ip_filter/main.cpp)
add_library(ip_filter ${PROJECT_SOURCE_DIR}/ip_filter/ip_filter.cpp)

#test: version
add_executable(test_version_run ${PROJECT_SOURCE_DIR}/test_version.cpp)

set_target_properties(test_version_run 
	PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
)
target_link_libraries(test_version_run
    ${Boost_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)


set_target_properties(
    	program_run
        ip_filter_run
        PROPERTIES 
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON)

if(CMAKE_BUILD_TYPE EQUAL "Release")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
else()
    # -DCMAKE_BUILD_TYPE=Debug --build
    set(CMAKE_BUILD_TYPE "Debug")
    set_target_properties(
    	program_run
        ip_filter_run 
        PROPERTIES
        COMPILE_OPTIONS "-g;-O0;-Wall;-Wextra;-Werror;-Wpedantic;")

    target_link_libraries(ip_filter_run PRIVATE -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer)
endif()

message("[+]BUILD_TYPE: " ${CMAKE_BUILD_TYPE})
message("[+]VERSION: " ${PROJECT_VERSION_MAJOR} "." ${PROJECT_VERSION_MINOR} "." ${PROJECT_VERSION_PATCH})


install(TARGETS program_run RUNTIME DESTINATION bin)

set(CPACK_GENERATOR DEB)

set(CPACK_PACKAGE_VERSION_MAJOR "${PROJECT_VERSION_MAJOR}")
set(CPACK_PACKAGE_VERSION_MINOR "${PROJECT_VERSION_MINOR}")
set(CPACK_PACKAGE_VERSION_PATCH "${PROJECT_VERSION_PATCH}")

set(CPACK_PACKAGE_CONTACT den.lightmare@gmail.com)

set(CPACK_DEBIAN_PACKAGE_SHLIBDEPS ON)

include(CPack)

#tests
enable_testing()
add_test(test_version_run ${PROJECT_SOURCE_DIR}/test_version)