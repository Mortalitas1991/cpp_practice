cmake_minimum_required(VERSION 3.12.4)

project(conan LANGUAGES C CXX)

include(${PROJECT_SOURCE_DIR}/conanbuildinfo.cmake)
conan_basic_setup()

set(src ${PROJECT_SOURCE_DIR}/main.cpp ${PROJECT_SOURCE_DIR}/conan.cpp)
add_executable(conan_run ${src})

# if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang")
#     target_link_libraries(conan_run PRIVATE "-lc++fs")
# endif()

# if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
#     target_link_libraries(conan_run PRIVATE "-lstdc++fs")
# endif()

if(CMAKE_BUILD_TYPE EQUAL "RELEASE")
    set(CMAKE_CXX_FLAGS_RELEASE "-O2")
else()
    # cmake .. -DCMAKE_BUILD_TYPE=DEBUG
    set(CMAKE_BUILD_TYPE "DEBUG")
    set_target_properties(
    	conan_run
        PROPERTIES
        CXX_STANDARD 17
        CXX_STANDARD_REQUIRED ON
        COMPILE_OPTIONS "-g;-O0;-Wall;-Wextra;-Werror;-Wpedantic;")

    target_link_libraries(conan_run PRIVATE -fsanitize=undefined -fsanitize=address -fno-omit-frame-pointer)
endif()
