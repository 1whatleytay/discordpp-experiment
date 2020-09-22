#include <discord/objects/channel.h>

namespace discord {
    Channel::Channel(const utility::Json &json) {
        id = json.at("id").string().as<Id>().get();
        type = json.at("type").number().as<Type>().get();
        guildId = json.at("guild_id").string().as<Id>();
        position = json.at("position").number().as<size_t>();
        name = json.at("name").string();
        topic = json.at("topic").string();
        nsfw = json.at("nsfw").boolean();
        lastMessage = json.at("last_message_id").string().as<Id>();
        bitrate = json.at("bitrate").number().as<size_t>();
        userLimit = json.at("user_limit").number().as<size_t>();
        icon = json.at("icon").string();
        owner = json.at("owner_id").string().as<Id>();
        applicationId = json.at("application_id").string().as<Id>();
        category = json.at("category").string().as<Id>();
        lastPinTimestamp = json.at("last_pin_timestamp").string();

        utility::Json overwritesJson = json.at("permission_overwrites");
        if (!overwritesJson.empty()) {
            overwrites.fill().get().resize(overwritesJson.getSize());
            for (size_t a = 0; a < overwrites.get().size(); a++) {
                overwrites.get()[a] = overwritesJson[a];
            }
        }

        utility::Json recipientsJson = json.at("recipients");
        if (!recipientsJson.empty()) {
            recipients.fill().get().resize(recipientsJson.getSize());
            for (size_t a = 0; a < recipients.get().size(); a++) {
                recipients.get()[a] = recipientsJson[a];
            }
        }
    }
}