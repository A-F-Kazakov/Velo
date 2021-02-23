message(STATUS "Build ${PROJECT_NAME} tests enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_test)

link_libraries(${PROJECT_NAME} Catch2::Catch2)
add_definitions(-DCATCH_CONFIG_MAIN)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_address_v4)
add_executable(${TARGET_NAME} address_v4)
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} -o address_v4.xml -r junit)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_address_v6)
add_executable(${TARGET_NAME} address_v6)
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} -o address_v6.xml -r junit)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_address)
add_executable(${TARGET_NAME} address)
add_test(NAME ${TARGET_NAME} COMMAND ${TARGET_NAME} -o address.xml -r junit)
