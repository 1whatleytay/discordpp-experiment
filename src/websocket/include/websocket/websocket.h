#pragma once

#include <http/http.h>

#include <utility/io.h>

#include <string>

namespace websocket {
    class Websocket : public utility::Io {
        utility::Io &io;

    public:
        Websocket(utility::Io &io, const http::Request &request);
        Websocket(utility::Io &io, const std::string &path);
    };
}