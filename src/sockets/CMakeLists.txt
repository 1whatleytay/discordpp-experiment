add_library(sockets STATIC
    include/sockets/sockets.h
    include/sockets/ssl.h

    src/sockets.cpp
    src/ssl.cpp)

target_include_directories(sockets PUBLIC include)
target_link_libraries(sockets PRIVATE ssl)
target_link_libraries(sockets PUBLIC utility)
