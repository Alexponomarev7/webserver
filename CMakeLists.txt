cmake_minimum_required(VERSION 3.9)

project(web_server)
add_subdirectory(server)

add_library(webserver STATIC ${LIB_CXX_SOURCES} ${LIB_ASM_SOURCES} ${LIB_HEADERS})
target_include_directories(webserver PUBLIC ${LIB_INCLUDE_PATH})
target_link_libraries(webserver PUBLIC pthread)

set(CMAKE_CXX_STANDARD 17)