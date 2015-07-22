#####################################################
# Project XShader(XSR)

cmake_minimum_required(VERSION 2.6)

project(XShader)

include_directories("./src")

add_library(XShader STATIC "src/xsr/ast.cpp" "src/xsr/lang.lex.yy.cpp" "src/xsr/lang.tab.cpp")

