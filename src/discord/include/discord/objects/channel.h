#pragma once

#include <discord/id.h>

#include <utility/json.h>

namespace discord {
    using utility::Optional;

    class Channel {
    public:
        enum class Type {
            GuildText,
            DirectMessage,
            GuildVoice,
            GroupMessage,
            GuildCategory,
            GuildNews,
            GuildStore,
        };

        Id id;
        Type type;
        Optional<Id> guildId;
        Optional<size_t> position;
        Optional<std::vector<utility::Json>> overwrites;
        Optional<std::string> name;
        Optional<std::string> topic;
        Optional<bool> nsfw;
        Optional<Id> lastMessage;
        Optional<size_t> bitrate;
        Optional<size_t> userLimit;
        Optional<std::vector<utility::Json>> recipients;
        Optional<std::string> icon;
        Optional<Id> owner;
        Optional<Id> applicationId;
        Optional<Id> category;
        Optional<std::string> lastPinTimestamp;

        explicit Channel(const utility::Json &json);
    };
}