cmake_minimum_required(VERSION 3.9)

get_filename_component(PROJECT_DIR_NAME ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${PROJECT_DIR_NAME} 
	VERSION 0.0.1 
	LANGUAGES CXX
	DESCRIPTION "Describe & deploy net protocol with simply a JSON file.")



set(SRC
        ../src/net_stack.cpp
	../src/parse_engine.cpp
	../src/parse_engine_decode_pop.cpp
	../src/parse_engine_encode_pop.cpp
	../src/proto_compiler.cpp
)

set(INCLUDE
        ../include/net_stack.h
	../include/packet.h
	../include/parse_engine.h
	../include/sized_mask.h
	../include/proto_compiler.h
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

find_package(GTest REQUIRED)

add_executable(PROJECT_DIR_NAME main.cpp)
target_link_libraries(PROJECT_DIR_NAME GTest::GTest GTest::Main)


