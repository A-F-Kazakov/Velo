message(STATUS "Build ${PROJECT_NAME} tests enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_test)

link_libraries(${PROJECT_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_point)

add_executable(${TARGET_NAME} point)
add_test(${TARGET_NAME} ${TARGET_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_distance)

add_executable(${TARGET_NAME} distance)
add_test(${TARGET_NAME} ${TARGET_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_line)

add_executable(${TARGET_NAME} line)
add_test(${TARGET_NAME} ${TARGET_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_intersect)

add_executable(${TARGET_NAME} intersect)
add_test(${TARGET_NAME} ${TARGET_NAME})
