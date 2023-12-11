cmake_minimum_required(VERSION 3.20)

project(tree)

set(CMAKE_CXX_STANDARD          17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS        OFF)

set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g -fsanitize=address,alignment,bool,bounds,enum,float-cast-overflow,float-divide-by-zero,integer-divide-by-zero,nonnull-attribute,null,object-size,return,returns-nonnull-attribute,shift,signed-integer-overflow,undefined,unreachable,vla-bound,vptr")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG")

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif()

add_executable(tree      ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
add_executable(tree_comp ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp)
target_compile_options(tree_comp PUBLIC -DCOMPARING)

target_include_directories(tree      PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(tree      PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_include_directories(tree_comp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/../include)
target_include_directories(tree_comp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)


