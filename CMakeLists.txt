cmake_minimum_required(VERSION 3.9)

get_filename_component(PROJECT_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
string(TOLOWER ${PROJECT_DIR_NAME} PROJECT_NAME)
project(${PROJECT_DIR_NAME} 
	VERSION 0.0.1 
	LANGUAGES CXX
	DESCRIPTION "Describe & deploy net protocol with simply a JSON file.")



set(SRC
	src/net_stack.cpp
	src/parse_engine.cpp
	src/parse_engine_decode_pop.cpp
	src/parse_engine_encode_pop.cpp
	src/proto_compiler.cpp
)

set(INCLUDE
	include/net_stack.h
	include/packet.h
	include/parse_engine.h
	include/proto_compiler.h
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -fPIC")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -flto")

# If no build type is set, the default is Release
if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release)
endif(NOT CMAKE_BUILD_TYPE)

find_package(PkgConfig)
pkg_check_modules(LIBPARSLEY REQUIRED libagio)

include_directories(/usr/local/include)
include_directories(./include)

add_library(${PROJECT_NAME} SHARED
	${INCLUDE} ${SRC}
)

target_link_libraries(${PROJECT_DIR_NAME} agio)


# set_target_properties(${PROJECT_DIR_NAME} PROPERTIES SOVERSION 1)
# set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${PROJECT_VERSION})

# INSTALL
include(GNUInstallDirs)

configure_file(${PROJECT_NAME}.pc.in ${PROJECT_NAME}.pc @ONLY)
install(FILES ${CMAKE_CURRENT_BINARY_DIR}/${PROJECT_NAME}.pc
        DESTINATION lib/pkgconfig)

install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION lib)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/
	DESTINATION include/${PROJECT_NAME}
	USE_SOURCE_PERMISSIONS
	FILES_MATCHING PATTERN "${PROJECT_DIR_NAME}/include/*.h")



