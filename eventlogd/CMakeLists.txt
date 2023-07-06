# Copyright 2023 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(eventlogd
        VERSION 1.0
        DESCRIPTION "Event Log Server executable (service/daemon)"
        LANGUAGES CXX)

add_executable(eventlogd src/eventlogd.cpp src/eventlogserver.cpp src/eventlogserver.h)

target_include_directories(eventlogd PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(eventlogd PRIVATE ${utillib_SOURCE_DIR}/include)
target_include_directories(eventlogd PRIVATE ${workflowlib_SOURCE_DIR}/include)
target_include_directories(eventlogd PRIVATE ${workflowapp_SOURCE_DIR}/include)

target_compile_definitions(eventlogd PRIVATE XML_STATIC)

if (MINGW)
    target_link_options(eventlogd PRIVATE -static)
endif ()

if (MSVC)
    target_compile_definitions(eventlogd PRIVATE _WIN32_WINNT=0x0A00)
endif ()

target_link_libraries(eventlogd PRIVATE workflowserv)
target_link_libraries(eventlogd PRIVATE ods)
target_link_libraries(eventlogd PRIVATE workflow)
target_link_libraries(eventlogd PRIVATE mdf)
target_link_libraries(eventlogd PRIVATE util)
target_link_libraries(eventlogd PRIVATE ${EXPAT_LIBRARIES})
target_link_libraries(eventlogd PRIVATE ${Boost_LIBRARIES})
target_link_libraries(eventlogd PRIVATE ${SQLite3_LIBRARIES})
target_link_libraries(eventlogd PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpq.lib)
target_link_libraries(eventlogd PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgtypes.lib)
target_link_libraries(eventlogd PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgport.lib)
target_link_libraries(eventlogd PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgcommon.lib)
target_link_libraries(eventlogd PRIVATE ${OPENSSL_LIBRARIES})
target_link_libraries(eventlogd PRIVATE ${Protobuf_LIBRARIES})
target_link_libraries(eventlogd PRIVATE ${Protobuf_PROTOC_LIBRARIES})
target_link_libraries(eventlogd PRIVATE absl::log)
target_link_libraries(eventlogd PRIVATE absl::log_internal_check_op)
target_link_libraries(eventlogd PRIVATE utf8_range::utf8_range)
target_link_libraries(eventlogd PRIVATE utf8_range::utf8_validity)
target_link_libraries(eventlogd PRIVATE gRPC::grpc++)

if (WIN32)
    #target_link_libraries(eventlogd PRIVATE iconv)
    #target_link_libraries(eventlogd PRIVATE bcrypt)
    target_link_libraries(eventlogd PRIVATE ws2_32)
    target_link_libraries(eventlogd PRIVATE mswsock)
    target_link_libraries(eventlogd PRIVATE secur32)
    target_link_libraries(eventlogd PRIVATE crypt32)
endif ()
