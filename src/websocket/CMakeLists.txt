add_library(websocket STATIC
    include/websocket/websocket.h

    src/websocket.cpp)

target_include_directories(websocket PUBLIC include)
target_link_libraries(websocket PUBLIC http sockets utility)
