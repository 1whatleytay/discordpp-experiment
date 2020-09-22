#pragma once

#include <utility/io.h>

#include <string>
#include <vector>
#include <unordered_map>

namespace http {
    using Headers = std::unordered_map<std::string, std::string>;

    class Request {
    public:
        uint32_t major = 1;
        uint32_t minor = 1;

        std::string method = "GET";
        std::string path = "/";

        Headers headers;
        std::vector<uint8_t> body;

        bool send(utility::Io &io);
        Request receive(utility::Io &io);

        Request header(const std::string &name, const std::string &content) const;

        Request() = default;
        explicit Request(std::string path);
        Request(std::string path, std::string method);
    };

    class Response {
    public:
        uint32_t major = 1;
        uint32_t minor = 1;

        uint32_t statusCode = 200;
        std::string statusString = "OK";

        Headers headers;
        std::vector<uint8_t> body;

        bool send(utility::Io &io);
        Response receive(utility::Io &io);

        Response header(const std::string &name, const std::string &content) const;

        Response() = default;
        explicit Response(std::vector<uint8_t> body);
    };
}