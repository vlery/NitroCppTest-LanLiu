
cmake_minimum_required(VERSION 3.6)


file(COPY include DESTINATION .)
file(COPY test.json DESTINATION .)
file(COPY result.json DESTINATION .)
include_directories( include )


project(RectIntersection)
add_library(MyLibrary CustomStruct.cpp RectDef.cpp)


add_executable(RectIntersection main.cpp)


target_link_libraries(RectIntersection MyLibrary)
set_property(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT RectIntersection)

