#pragma once

#include <memory>

namespace utility {
    template <typename T>
    class Optional {
        std::unique_ptr<T> value;
    public:
        T &get() const {
            if (!value)
                throw std::runtime_error("Tried to get value of optional.");

            return *value.get();
        }
        void set(T &newValue) {
            value.reset(new T(newValue));
        }
        bool empty() const {
            return value == nullptr;
        }
        void clear() {
            value.reset();
        }

        Optional<T> &fill() {
            if (!value)
                value.reset(new T());

            return *this;
        }

        template <typename M>
        Optional<M> as() {
            if (empty())
                return Optional<M>();

            return Optional<M>(M(get()));
        }

        Optional() = default;
        Optional(T value) {
            set(value);
        }
    };
}