message(STATUS "Build ${PROJECT_NAME} examples enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_example)

link_libraries(${PROJECT_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_performance)
add_executable(${TARGET_NAME} performance.cpp)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_argument_parser)
add_executable(${TARGET_NAME} argument_parse.cpp)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_file_watcher)
add_executable(${TARGET_HEAD} file_watch.cpp)
target_link_libraries(${TARGET_HEAD} PUBLIC fs)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_logger)
add_executable(${TARGET_NAME} logger_example.cpp)
