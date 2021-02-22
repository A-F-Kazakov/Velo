message(STATUS "Build ${PROJECT_NAME} examples enabled")

set(EXAMPLES_HEAD ${PROJECT_NAME}_example)

link_libraries(${PROJECT_NAME})

#
set(EXAMPLE_NAME ${EXAMPLES_HEAD}_tcp_echo_server)
add_executable(${EXAMPLE_NAME} tcp_echo_server)

#
set(EXAMPLE_NAME ${EXAMPLES_HEAD}_tcp_echo_client)
add_executable(${EXAMPLE_NAME} tcp_echo_client)

#
set(EXAMPLE_NAME ${EXAMPLES_HEAD}_udp_echo_server)
add_executable(${EXAMPLE_NAME} udp_echo_server)

#
set(EXAMPLE_NAME ${EXAMPLES_HEAD}_udp_echo_client)
add_executable(${EXAMPLE_NAME} udp_echo_client)

if(SSL_SUPPORT)
	#
	set(EXAMPLE_NAME ${EXAMPLES_HEAD}_ssl_echo_server)
	add_executable(${EXAMPLE_NAME} ssl_echo_server)

	#
	set(EXAMPLE_NAME ${EXAMPLES_HEAD}_ssl_echo_client)
	add_executable(${EXAMPLE_NAME} ssl_echo_client)
endif()
