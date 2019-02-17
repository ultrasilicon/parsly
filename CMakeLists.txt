cmake_minimum_required(VERSION 3.9)
project(parsely VERSION 1.0.0 DESCRIPTION "Describe & deploy net protocol with simply a JSON file.")
set_target_properties(mylib PROPERTIES SOVERSION 1)


set_target_properties(parsely PROPERTIES VERSION ${PROJECT_VERSION})

add_library(parsely SHARED
	src/net_stack.cpp
	src/packet.cpp
	src/parse_engine.cpp
	src/parse_engine_decode_pop.cpp
	src/parse_engine_encode_pop.cpp
)

target_include_directories(parsely PRIVATE include)
target_include_directories(parsely PRIVATE src)


# INSTALL
include(GNUInstallDirs)
install(TARGETS parsely
    	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

configure_file(parsely.pc.in parsely.pc @ONLY)



