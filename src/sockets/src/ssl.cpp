#include <sockets/ssl.h>

#include <openssl/ssl.h>

namespace sockets {
    std::atomic<bool> SslSocket::initialized(false);

    size_t SslSocket::read(void *data, size_t size) {
        size_t bytesRead = 0;
        if (SSL_read_ex(ssl, data, size, &bytesRead) != 1)
            throw std::runtime_error("Ssl Socket read error.");

        return bytesRead;
    }
    size_t SslSocket::write(const void *data, size_t size) {
        size_t bytesRead = 0;
        if (SSL_write_ex(ssl, data, size, &bytesRead) != 1)
            throw std::runtime_error("Ssl Socket write error.");

        return bytesRead;
    }

    SslSocket::SslSocket(int32_t socket) {
        // hopefully this will prevent any tricky thread issues
        if (!initialized) {
            initialized = true;
            SSL_library_init();
        }

        const SSL_METHOD *method = SSLv23_method();
        assert(method);
        context = SSL_CTX_new(method);
        assert(context);
        ssl = SSL_new(context);
        assert(ssl);

        int error = SSL_set_fd(ssl, socket);
        assert(error == 1);
    }

    SslSocket::SslSocket(const ClientSocket &socket) : SslSocket(socket.getSocket()) {
        int error = SSL_connect(ssl);
        assert(error == 1);
    }

    SslSocket::SslSocket(const ConnectionSocket &socket) : SslSocket(socket.getSocket()) {
        int error = SSL_accept(ssl);
        assert(error == 1);
    }

    SslSocket::~SslSocket() {
        SSL_shutdown(ssl);
        SSL_free(ssl);

        SSL_CTX_free(context);
    }
}