add_library(discord STATIC
    include/discord/id.h
    include/discord/discord.h

    include/discord/objects/channel.h

    src/id.cpp
    src/discord.cpp

    src/objects/channel.cpp)

target_include_directories(discord PUBLIC include)
target_link_libraries(discord PUBLIC http sockets utility fmt)