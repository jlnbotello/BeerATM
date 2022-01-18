cmake_minimum_required(VERSION 3.0.0)

set(PROJECT_NAME
    BeerAtm
)
set(SOURCE_DIR
    src
)

set(SOURCE
    ${SOURCE_DIR}/main.cc
)

set(TEST_DIR
    test
)

set(TEST
    ${TEST_DIR}/dispenser/dispenser_test.cc
)

set(LIBRARIES_DIR
    lib
)
set(LIBRARIES 

)

# specify the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")


# set the project name and version
project(${PROJECT_NAME} 
    VERSION 0.1
    DESCRIPTION "Beer ATM System"
    LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  # Specify the commit you depend on and update it regularly.
  URL https://github.com/google/googletest/archive/609281088cfefc76f9d0ce82e1ff6c30cc3591e5.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(dispenser_test ${TEST})
include_directories(include)
target_link_libraries(dispenser_test gtest_main)
enable_testing()
add_test(NAME DispenserTest COMMAND dispenser_test)