message(STATUS "Build ${PROJECT_NAME} examples enabled")

set(EXAMPLES_HEAD ${PROJECT_NAME}_example)

find_package(Threads)

link_libraries(Network)

set(EXAMPLE_NAME ${EXAMPLES_HEAD}_tcp_echo_server)

#
add_executable(${EXAMPLE_NAME} tcp_echo_server.cpp)
target_link_libraries(${EXAMPLE_NAME} Threads::Threads)

#
set(EXAMPLE_NAME ${EXAMPLES_HEAD}_tcp_echo_client)
add_executable(${EXAMPLE_NAME} tcp_echo_client.cpp)

#
set(EXAMPLE_NAME ${EXAMPLES_HEAD}_udp_echo_server)
add_executable(${EXAMPLE_NAME} udp_echo_server.cpp)

#
set(EXAMPLE_NAME ${EXAMPLES_HEAD}_udp_echo_client)
add_executable(${EXAMPLE_NAME} udp_echo_client.cpp)

if(SSL_SUPPORT)
	#
	set(EXAMPLE_NAME ${EXAMPLES_HEAD}_ssl_echo_server)
	add_executable(${EXAMPLE_NAME} ssl_echo_server.cpp)
	target_link_libraries(${EXAMPLE_NAME} PUBLIC Threads::Threads)

	#
	set(EXAMPLE_NAME ${EXAMPLES_HEAD}_ssl_echo_client )
	add_executable(${EXAMPLE_NAME} ssl_echo_client.cpp)
endif()
