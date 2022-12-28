project(set_app)
set(CMAKE_CXX_STANDARD 14)


set(SOURCES
        main.cpp
)

set(INCLUDE_DIR
        ./include
)

add_executable(set_app ${SOURCES} ${HEADERS})
target_include_directories(set_app PUBLIC ${INCLUDE_DIR})


add_subdirectory(tests)

