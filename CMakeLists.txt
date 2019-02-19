cmake_minimum_required(VERSION 3.9)

get_filename_component(PROJECT_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_DIR_NAME} 
	VERSION 0.0.1 
	LANGUAGES CXX
	DESCRIPTION "Describe & deploy net protocol with simply a JSON file.")



set(SRC
	src/net_stack.cpp
	src/parse_engine.cpp
	src/parse_engine_decode_pop.cpp
	src/parse_engine_encode_pop.cpp
)

set(INCLUDE
	include/net_stack.h
	include/packet.h
	include/parse_engine.h
	include/sized_mask.h
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -flto")



include_directories(/usr/local/include)
include_directories(./include)
# target_include_directories(${PROJECT_DIR_NAME} PRIVATE src)

add_library(${PROJECT_DIR_NAME} SHARED
	${INCLUDE} ${SRC}
)

# set_target_properties(${PROJECT_DIR_NAME} PROPERTIES SOVERSION 1)
set_target_properties(${PROJECT_DIR_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# INSTALL
include(GNUInstallDirs)
install(TARGETS ${PROJECT_DIR_NAME}
    	LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    	PUBLIC_HEADER DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
if(NOT CMAKE_INSTALL_PREFIX)
    set(CMAKE_INSTALL_PREFIX /usr/local)
endif(NOT CMAKE_INSTALL_PREFIX)

configure_file(${PROJECT_DIR_NAME}.pc.in ${PROJECT_DIR_NAME}.pc @ONLY)



