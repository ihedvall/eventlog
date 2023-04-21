# Copyright 2023 Ingemar Hedvall
# SPDX-License-Identifier: MIT
cmake_minimum_required(VERSION 3.20)
project(EventLogExplorer
        VERSION 1.0
        DESCRIPTION "Event Log Explorer"
        LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

include("../script/wxwidgets.cmake")

add_executable(eventlogexplorer
        src/eventexplorer.cpp src/eventexplorer.h
        src/mainframe.cpp src/mainframe.h
        src/eventdocument.cpp src/eventdocument.h
        src/eventview.cpp src/eventview.h
        src/eventexplorer.rc
        src/childframe.cpp src/childframe.h
        src/windowid.h )


target_include_directories(eventlogexplorer PRIVATE ${wxWidgets_INCLUDE_DIRS})
target_include_directories(eventlogexplorer PRIVATE ${Boost_INCLUDE_DIRS})
target_include_directories(eventlogexplorer PRIVATE ods)
target_include_directories(eventlogexplorer PRIVATE util)
target_include_directories(eventlogexplorer PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")

target_compile_definitions(eventlogexplorer PRIVATE XML_STATIC)

if (MINGW)
target_link_options(eventlogexplorer PRIVATE -mwindows -static -fstack-protector)
endif()

if (MSVC)
target_link_options(eventlogexplorer PRIVATE /SUBSYSTEM:WINDOWS)
target_compile_definitions(eventlogexplorer PRIVATE _WIN32_WINNT=0x0A00)
endif()

target_link_libraries(eventlogexplorer PRIVATE ods)
target_link_libraries(eventlogexplorer PRIVATE mdf)
target_link_libraries(eventlogexplorer PRIVATE util)
target_link_libraries(eventlogexplorer PRIVATE expat)
target_link_libraries(eventlogexplorer PRIVATE ${wxWidgets_LIBRARIES})
target_link_libraries(eventlogexplorer PRIVATE ${Boost_LIBRARIES})
target_link_libraries(eventlogexplorer PRIVATE ${ZLIB_LIBRARIES})
target_link_libraries(eventlogexplorer PRIVATE ${OPENSSL_CRYPTO_LIBRARY} )
target_link_libraries(eventlogexplorer PRIVATE ${SQLite3_LIBRARIES})
target_link_libraries(eventlogexplorer PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpq.lib)
target_link_libraries(eventlogexplorer PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgtypes.lib)
target_link_libraries(eventlogexplorer PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgport.lib)
target_link_libraries(eventlogexplorer PRIVATE ${PostgreSQL_LIBRARY_DIRS}/libpgcommon.lib)

if (MINGW)
    target_link_libraries(eventlogexplorer PRIVATE iconv)
endif()

if (WIN32)
    target_link_libraries(eventlogexplorer PRIVATE secur32)
    target_link_libraries(eventlogexplorer PRIVATE crypt32)
    target_link_libraries(eventlogexplorer PRIVATE bcrypt)
    target_link_libraries(eventlogexplorer PRIVATE ws2_32)
endif()
