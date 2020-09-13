message(STATUS "Build ${PROJECT_NAME} tests enabled")

set(TARGET_NAME_HEAD ${PROJECT_NAME}_test)

find_package(Boost COMPONENTS unit_test_framework REQUIRED)

enable_testing()

add_definitions(-DBOOST_TEST_DYN_LINK)

#

set(TARGET_NAME ${TARGET_NAME_HEAD}_numbers)

add_executable(${TARGET_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/numeric.cpp)
target_link_libraries(${TARGET_NAME} PRIVATE ${Boost_LIBRARIES} generic)

add_test(${TARGET_NAME} ${TARGET_NAME})
