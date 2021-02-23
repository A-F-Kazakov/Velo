message(STATUS "Build ${PROJECT_NAME} tests enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_test)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_numbers)

add_executable(${TARGET_NAME} numeric)
target_link_libraries(${TARGET_NAME} PRIVATE Generic Catch2::Catch2)
target_compile_definitions(${TARGET_NAME} PRIVATE CATCH_CONFIG_MAIN)

add_test(${TARGET_NAME} ${TARGET_NAME})
