#pragma once

#include <discord/id.h>
#include <discord/objects/channel.h>

#include <sockets/ssl.h>

#include <http/http.h>

#include <string>

namespace discord {
    class Client {
        std::string token;

        utility::Json send(const std::string &extension);
    public:
        Channel getChannel(const Id &id);

        explicit Client(std::string token);
    };
}