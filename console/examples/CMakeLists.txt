message(STATUS "Build ${PROJECT_NAME} examples enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_example)

#

set(TARGET_NAME ${PROJECT_NAME}_console)
add_executable(${TARGET_NAME} console.cpp)
target_link_libraries(${TARGET_NAME} Console)
