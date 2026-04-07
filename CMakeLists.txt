cmake_minimum_required(VERSION 3.10.0)
project(Algos_kurs VERSION 0.1.0 LANGUAGES C CXX)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers/classes)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/headers/structures)
add_executable(Algos_kurs 
    main.cpp
    cpp/classes/Client.cpp
    cpp/structures/ClientAVL.cpp
    )

