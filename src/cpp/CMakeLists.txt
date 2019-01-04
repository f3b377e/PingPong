cmake_minimum_required(VERSION 3.12)
project(pingpong)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(lib)
# set(CMAKE_LIBRARY_PATH ${CMAKE_CURRENT_SOURCE_DIR}/lib)
# set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/lib/)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/build)

find_library(mylibpath CppToUnity)
find_package (Threads REQUIRED)
find_package (OpenCV REQUIRED)

set(PINGPONG_SRC
        net/networksocket.cpp
        net/networksocket.hpp
        thread/threads.cpp
        thread/threads.hpp
        main.cpp
        commons.hpp)

set(NAMED_SEMAPHORE_FIRST_SRC
        named\ semaphore/first.cpp "named semaphore/common.hpp")

set(NAMED_SEMAPHORE_SECOND_SRC
        named\ semaphore/second.cpp "named semaphore/common.hpp")

set(UNNAMED_SEMAPHORE_FIRST_SRC
        "unnamed semaphore/first.cpp" "unnamed semaphore/common.hpp")

set(UNNAMED_SEMAPHORE_SECOND_SRC
        "unnamed semaphore/second.cpp" "unnamed semaphore/common.hpp")

set(BALL_TRACKING_SRC
        ball\ tracking/ball_tracking.cpp)

add_executable(pingpong ${PINGPONG_SRC})
target_link_libraries (pingpong ${OpenCV_LIBS} ${CMAKE_THREAD_LIBS_INIT} ${mylibpath})

add_executable(namedsem_first ${NAMED_SEMAPHORE_FIRST_SRC})
add_executable(namedsem_second ${NAMED_SEMAPHORE_SECOND_SRC})
target_link_libraries (namedsem_first ${CMAKE_THREAD_LIBS_INIT} rt)
target_link_libraries (namedsem_second ${CMAKE_THREAD_LIBS_INIT} rt)

add_executable(unnamed_first ${UNNAMED_SEMAPHORE_FIRST_SRC})
add_executable(unnamed_second ${UNNAMED_SEMAPHORE_SECOND_SRC})
target_link_libraries (unnamed_first ${CMAKE_THREAD_LIBS_INIT} rt)
target_link_libraries (unnamed_second ${CMAKE_THREAD_LIBS_INIT} rt)

add_executable(ballTracking ${BALL_TRACKING_SRC})
target_link_libraries (ballTracking ${OpenCV_LIBS})