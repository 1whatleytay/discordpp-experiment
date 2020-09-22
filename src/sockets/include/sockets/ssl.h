#include <climits>

#pragma once

#include <sockets/sockets.h>

#include <utility/io.h>

#include <atomic>
#include <cstdint>

using SSL = struct ssl_st;
using SSL_CTX = struct ssl_ctx_st;

namespace sockets {
    class SslSocket : public utility::Io {
        static std::atomic<bool> initialized;

        SSL *ssl = nullptr;
        SSL_CTX *context = nullptr;

        explicit SslSocket(int32_t socket);
    public:
        size_t read(void *data, size_t size) override;
        size_t write(const void *data, size_t size) override;

        SslSocket() = default;
        explicit SslSocket(const ClientSocket &socket);
        explicit SslSocket(const ConnectionSocket &socket);
        ~SslSocket() override;
    };
}