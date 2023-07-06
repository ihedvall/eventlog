# Copyright 2023 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(eventlog
        VERSION 1.0
        DESCRIPTION "Event Log Applications"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include(CMakePrintHelpers)


include(script/utillib.cmake)
include(script/mdflib.cmake)
include(script/odslib.cmake)
include(script/workflowlib.cmake)
include(script/workflow.cmake)
include(script/boost.cmake)
include(script/postgresql.cmake)
include(script/openssl.cmake)
include(script/sqlite3.cmake)
include(script/protobuf.cmake)
include(script/grpc.cmake)

add_subdirectory(eventlogd)
add_subdirectory(eventlogexplorer)

include(InstallRequiredSystemLibraries)
message(STATUS "Run-Time Libs : " ${CMAKE_INSTALL_SYSTEM_RUNTIME_LIBS})
message(STATUS "Run-Time Dest : " ${CMAKE_INSTALL_SYSTEM_RUNTIME_DESTINATION})
message(STATUS "Run-Time Components : " ${CMAKE_INSTALL_SYSTEM_RUNTIME_COMPONENT})