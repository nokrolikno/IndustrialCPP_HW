
project(tests)

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(SOURCE_FILES
        ./tests.cpp
   )

set(INCLUDE_DIR
        ../include
   )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lgtest -fPIC")

add_executable(tests ${SOURCE_FILES})

target_include_directories(tests PUBLIC ${INCLUDE_DIR} ${GTEST_INCLUDE_DIRS})

target_link_libraries(tests PUBLIC gtest gtest_main)
