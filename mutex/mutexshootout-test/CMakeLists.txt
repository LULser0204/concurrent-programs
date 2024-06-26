cmake_minimum_required(VERSION 2.6)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS OFF)

project(MutexShootout)

find_package(Boost REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})
link_directories(${BOOST_LIBRARYDIR})

if (UNIX)
    find_package(Threads)
    find_package(Boost COMPONENTS system REQUIRED)
    add_definitions(-DUSE_LINUX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ")
    set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ")
endif()

add_executable(MutexShootout main.cpp MurmurHash3.cpp lru_cache.hpp MurmurHash3.h hashing.hpp alt_mutex.hpp stopwatch.hpp atomic.h cond.h futex.h mutex.h spinlock.h)

if (EXISTS "${CMAKE_SOURCE_DIR}/skinny_mutex/skinny_mutex.h")
    message("Found skinny_mutex.h at ${CMAKE_SOURCE_DIR}/skinny_mutex/skinny_mutex.h")
    target_include_directories(MutexShootout PRIVATE ${CMAKE_SOURCE_DIR}/skinny_mutex)
    target_sources(MutexShootout PRIVATE ${CMAKE_SOURCE_DIR}/skinny_mutex/skinny_mutex.c)
    target_compile_definitions(MutexShootout PRIVATE USE_SKINNY_MUTEX)
else()
    message("skinny_mutex.h not found")
    
endif()

if (UNIX)
    target_link_libraries(MutexShootout ${Boost_SYSTEM_LIBRARY})
    target_link_libraries(MutexShootout ${CMAKE_THREAD_LIBS_INIT})
    set(CMAKE_BUILD_TYPE Release)
endif()

