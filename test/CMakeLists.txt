cmake_minimum_required(VERSION 3.9)

project(test_parsly
    LANGUAGES CXX)

set(LIB_NAME test_parsly)

set(INCLUDE
    ${PROJECT_SOURCE_DIR}/test_parse_engine.h
    ${PROJECT_SOURCE_DIR}/test_proto_compiler.h
    ${PROJECT_SOURCE_DIR}/common.h
    ${PROJECT_SOURCE_DIR}/../include/net_stack.h
    ${PROJECT_SOURCE_DIR}/../include/packet.h
    ${PROJECT_SOURCE_DIR}/../include/parse_engine.h
    ${PROJECT_SOURCE_DIR}/../include/sized_mask.h
    ${PROJECT_SOURCE_DIR}/../include/proto_compiler.h
)

set(SRC
    ${PROJECT_SOURCE_DIR}/main.cpp
    ${PROJECT_SOURCE_DIR}/../src/net_stack.cpp
    ${PROJECT_SOURCE_DIR}/../src/parse_engine.cpp
    ${PROJECT_SOURCE_DIR}/../src/parse_engine_decode_pop.cpp
    ${PROJECT_SOURCE_DIR}/../src/parse_engine_encode_pop.cpp
    ${PROJECT_SOURCE_DIR}/../src/proto_compiler.cpp
)

set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")
set(CMAKE_CXX_FLAGS_DEBUG "-g -DDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-O2 -DNDEBUG -flto")


include_directories(/usr/local/include)
include_directories(../include)

find_package(GTest REQUIRED)

add_executable(${PROJECT_NAME}
    ${INCLUDE} ${SRC})

target_include_directories(${PROJECT_NAME}
    PRIVATE ${CMAKE_PREFIX_PATH}/include
    PRIVATE ${PROJECT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME}
    GTest::GTest GTest::Main)


