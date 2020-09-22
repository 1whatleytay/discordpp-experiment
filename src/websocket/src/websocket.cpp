#include <websocket/websocket.h>

#include <http/http.h>

namespace websocket {
    Websocket::Websocket(utility::Io &io, const http::Request &request) : io(io) {
        request
            .header("Upgrade", "websocket")
            .header("Connection", "Upgrade")
            .header("Sec-WebSocket-Key", "SGVsbG8gV29ybGQh") // Hello World!
            .send(io);

        auto response = http::Response().receive(io);


    }

    Websocket::Websocket(utility::Io &io, const std::string &path) : Websocket(io, http::Request(path)) {}
}