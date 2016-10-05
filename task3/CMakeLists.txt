cmake_minimum_required(VERSION 3.3)

project(rational)

add_library(rational rational.cpp)
install(FILES rational.h DESTINATION include)
install(TARGETS rational DESTINATION lib)
