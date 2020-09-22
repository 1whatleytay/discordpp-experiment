#include <discord/id.h>

namespace discord {
    std::string Id::toString() const { return std::to_string(id); }

    Id::Id(uint64_t id) : id(id) { }
    Id::Id(const std::string &text) : id(std::stoull(text)) { }
}