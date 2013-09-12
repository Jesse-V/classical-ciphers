cmake_minimum_required(VERSION 2.6)

project(classical-ciphers)

include_directories(.)

#organized by importance
add_executable(ClassicalCiphers
    main.cpp
)

target_link_libraries(ClassicalCiphers)
