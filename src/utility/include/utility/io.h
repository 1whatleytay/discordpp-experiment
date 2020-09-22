s#pragma once

#include <cstdlib>

namespace utility {
    class Io {
    public:
        virtual size_t read(void *data, size_t size) = 0;
        virtual size_t write(const void *data, size_t size) = 0;

        virtual ~Io() = default;
    };
}
