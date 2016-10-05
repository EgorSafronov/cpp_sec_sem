cmake_minimum_required(VERSION 3.3)

project(rational)

add_library(rational rational.cpp)
install(FILES rational.hpp DESTINATION include)
install(TARGETS rational DESTINATION lib)
