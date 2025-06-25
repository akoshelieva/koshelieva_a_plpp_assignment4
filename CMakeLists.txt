cmake_minimum_required(VERSION 3.10)
project(koshelieva_a_plpp_assignment4)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(ceasar SHARED ${CMAKE_SOURCE_DIR}/ceasar.cpp)
set_target_properties(ceasar PROPERTIES WINDOWS_EXPORT_ALL_SYMBOLS ON)

add_executable(koshelieva_a_plpp_assignment4 main.cpp
        text_editor.cpp
        Line.cpp
        TextLine.cpp
        CheckList.cpp
        ContactLine.cpp
caesar_cipher.cpp)

target_link_libraries(koshelieva_a_plpp_assignment4 PRIVATE ceasar)