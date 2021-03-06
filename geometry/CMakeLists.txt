project(Geometry VERSION 0.0.1)

string(TOUPPER ${PROJECT_NAME} PROJECT_NAME_UPPER)
string(TOLOWER ${PROJECT_NAME} PROJECT_NAME_LOWER)

set(${PROJECT_NAME_UPPER}_VERSION ${PROJECT_VERSION})
set(${PROJECT_NAME_UPPER}_VERSION_MAJOR ${PROJECT_VERSION_MAJOR})
set(${PROJECT_NAME_UPPER}_VERSION_MINOR ${PROJECT_VERSION_MINOR})
set(${PROJECT_NAME_UPPER}_VERSION_PATCH ${PROJECT_VERSION_PATCH})

message(STATUS "${PROJECT_NAME} Version: ${${PROJECT_NAME_UPPER}_VERSION_MAJOR}.${${PROJECT_NAME_UPPER}_VERSION_MINOR}.${${PROJECT_NAME_UPPER}_VERSION_PATCH}")

option(${PROJECT_NAME_UPPER}_BUILD_TESTS "Build ${PROJECT_NAME} tests" OFF)

#set(INCLUDE_DIR ${CURRENT_SOUCE_DIR}/include/${PROJECT_NAME_LOWER})

add_library(${PROJECT_NAME} INTERFACE)
target_compile_features(${PROJECT_NAME} INTERFACE cxx_std_17)
target_include_directories(${PROJECT_NAME}
	INTERFACE
		$<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include> 
		$<INSTALL_INTERFACE:include/${PROJECT_NAME_LOWER}>
)

#target_sources(${PROJECT_NAME}
#	INTERFACE
#		${INCLUDE_DIR}/algorithms/distance
#		${INCLUDE_DIR}/algorithms/equivalent
#		${INCLUDE_DIR}/algorithms/intersect
#		${INCLUDE_DIR}/algorithms/parallel
#		${INCLUDE_DIR}/basic_line
#		${INCLUDE_DIR}/basic_point
#		${INCLUDE_DIR}/flat/line
#		${INCLUDE_DIR}/flat/point
#		${INCLUDE_DIR}/flat/segment
#		${INCLUDE_DIR}/traits
#		${INCLUDE_DIR}/spatial/line
#		${INCLUDE_DIR}/spatial/point
#)

add_library(${CMAKE_PROJECT_NAME}::${PROJECT_NAME} ALIAS ${PROJECT_NAME})

install(EXPORT ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIB_DIR}/cmake/${PROJECT_NAME_LOWER} FILE ${PROJECT_NAME}Config.cmake)
install(TARGETS ${PROJECT_NAME}
	EXPORT ${PROJECT_NAME}
	RUNTIME DESTINATION bin COMPONENT ${PROJECT_NAME}
	LIBRARY DESTINATION lib COMPONENT ${PROJECT_NAME}
	ARCHIVE DESTINATION lib COMPONENT ${PROJECT_NAME}
)

if(${PROJECT_NAME_UPPER}_BUILD_TESTS)
	add_subdirectory(tests)
endif()

