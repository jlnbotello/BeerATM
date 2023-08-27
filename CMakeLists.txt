cmake_minimum_required(VERSION 3.13)

set(PROJECT_NAME P02)
set(PROJECT_DESC "Project")

set(SRC_DIR  projects/${PROJECT_NAME}/src)
set(INC_DIR  projects/${PROJECT_NAME}/inc)
set(TEST_DIR projects/${PROJECT_NAME}/test)

file(GLOB CPP_SOURCE
    ${SRC_DIR}/*.cc
)

file(GLOB C_SOURCE
    ${SRC_DIR}/*.c
)

set(SOURCE
    ${CPP_SOURCE}
    ${C_SOURCE}
)

file(GLOB CPP_TEST
    ${TEST_DIR}/*.cc
)

file(GLOB C_TEST
    ${TEST_DIR}/*.c
)

set(TEST
    ${CPP_TEST}
    ${C_TEST}
)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_COMPILER "g++.exe")
set(CMAKE_C_COMPILER "gcc.exe")
set(CMAKE_BUILD_TYPE "Debug")
# set the project name and version
project(${PROJECT_NAME} 
    VERSION 0.1
    DESCRIPTION ${PROJECT_DESC}
    LANGUAGES CXX C)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
if (${CMAKE_SYSTEM_NAME} STREQUAL CYGWIN)
	add_definitions(-DTEST_HAS_PTHREAD=0)
	set(gtest_disable_pthreads ON CACHE BOOL "" FORCE)
endif()
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
include_directories(${INC_DIR} build/_deps/googletest-src/googlemock/include build/_deps/googletest-src/googletest/include)
add_executable(${PROJECT_NAME} ${SOURCE} ${TEST})
target_link_libraries(${PROJECT_NAME}  gtest_main gmock gmock_main)
enable_testing()
add_test(NAME ${PROJECT_NAME} COMMAND ${PROJECT_NAME})