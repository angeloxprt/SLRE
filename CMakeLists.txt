cmake_minimum_required(VERSION 3.10)
project(SLRE_FFB_Injector)

add_library(version SHARED src/version.cpp)
target_link_libraries(version dinput8 dxguid)
set_target_properties(version PROPERTIES OUTPUT_NAME "version")
