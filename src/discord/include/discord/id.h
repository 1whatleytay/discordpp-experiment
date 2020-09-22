#pragma once

#include <string>

#include <utility/optional.h>

namespace discord {
    using utility::Optional;

    class Id {
    public:
        uint64_t id = 0;

        // get timestamp, process, worker, increment

        std::string toString() const;

        Id() = default;
        Id(uint64_t id);
        Id(const std::string &text);
    };
}