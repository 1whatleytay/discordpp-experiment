#pragma once

namespace utility {
    template <typename T>
    T swap(T value) {
        T result = 0;

        for (int a = 0; a < sizeof(value); a++) {
            result <<= 8;
            result |= ((value >> (a * 8)) & 0xFF);
        }

        return result;
    }

    template <typename T, typename N>
    T swap(T value) {
        return static_cast<T>(swap(static_cast<N>(value)));
    }
}