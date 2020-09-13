message(STATUS "Build ${PROJECT_NAME} examples enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_example)

link_libraries(${PROJECT_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_console)
add_executable(${TARGET_NAME} typelist.cpp)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_serializer)
add_executable(${TARGET_NAME} serializer.cc)
