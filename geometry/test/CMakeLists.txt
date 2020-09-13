message(STATUS "Build ${PROJECT_NAME} tests enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

enable_testing()

add_definitions(-DBOOST_TEST_DYN_LINK)
link_libraries(${Boost_LIBRARIES} ${PROJECT_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_point)

add_executable(${TARGET_NAME} point.cc)
target_compile_definitions(${TARGET_NAME} PRIVATE "-DBOOST_TEST_MODULE=${TARGET_NAME}")
add_test(${TARGET_NAME} ${TARGET_NAME

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_distance)

add_executable(${TARGET_NAME} distance.cc)
target_compile_definitions(${TARGET_NAME} PRIVATE "-DBOOST_TEST_MODULE=${TARGET_NAME}")
add_test(${TARGET_NAME} ${TARGET_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_line)

add_executable(${TARGET_NAME} line.cc)
target_compile_definitions(${TARGET_NAME} PRIVATE "-DBOOST_TEST_MODULE=${TARGET_NAME}")
add_test(${TARGET_NAME} ${TARGET_NAME})

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_intersect)

add_executable(${TARGET_NAME} intersect.cc)
target_compile_definitions(${TARGET_NAME} PRIVATE "-DBOOST_TEST_MODULE=${TARGET_NAME}")
add_test(${TARGET_NAME} ${TARGET_NAME})
