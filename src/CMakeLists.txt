add_subdirectory(utility)
add_subdirectory(sockets)
add_subdirectory(http)
add_subdirectory(websocket)
add_subdirectory(discord)

add_executable(discordpptest main.cpp)
target_link_libraries(discordpptest PUBLIC sockets http websocket discord fmt)
