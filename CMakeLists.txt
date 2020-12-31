# -DCMAKE_CXX_COMPILER=g++
# clang-tidy functions.cpp 
# -fdump-record-layouts - class hierarchy

cmake_minimum_required(VERSION 3.12.4)

project(cpp_practice VERSION 0.0.0$ENV{TRAVIS_BUILD_NUMBER} LANGUAGES C CXX)

find_package(Threads REQUIRED)
find_package(Boost REQUIRED)
# export BOOST_ROOT=/usr/local/${VERSION}
include_directories(${Boost_INCLUDE_DIRS})

#generate version
configure_file(${PROJECT_SOURCE_DIR}/version.h.in ${PROJECT_SOURCE_DIR}/version.h)

#main
set(progrum_srt
    ${PROJECT_SOURCE_DIR}/main.cpp 
    ${PROJECT_SOURCE_DIR}/version.cpp)
add_executable(program_run ${progrum_srt})

#test: version
add_executable(test_version_run ${PROJECT_SOURCE_DIR}/test_version.cpp ${PROJECT_SOURCE_DIR}/version.cpp)
set_target_properties(test_version_run 
	PROPERTIES
    COMPILE_DEFINITIONS BOOST_TEST_DYN_LINK
    INCLUDE_DIRECTORIES ${Boost_INCLUDE_DIRS}
)
target_link_libraries(test_version_run
    ${Boost_LIBRARIES}
    ${Boost_UNIT_TEST_FRAMEWORK_LIBRARY}
)

#ip filter
add_subdirectory(ip_filter)


if(CMAKE_BUILD_TYPE EQUAL "RELEASE")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
else()
    # cmake .. -DCMAKE_BUILD_TYPE=DEBUG
    set(CMAKE_BUILD_TYPE "DEBUG")
    set_target_properties(
    	program_run
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-g;-O0;-Wall;-Wextra;-Werror;-Wpedantic;")

    target_link_libraries(program_run PRIVATE -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer)
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
add_test(NAME test_version COMMAND test_version_run)