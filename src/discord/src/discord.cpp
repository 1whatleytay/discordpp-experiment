#include <discord/discord.h>

#include <fmt/format.h>

namespace discord {
    utility::Json Client::send(const std::string &extension) {
        // creating these every time might be too much
        sockets::ClientSocket client(443, { 162, 159, 133, 233 });
        sockets::SslSocket ssl(client);

        http::Request(fmt::format("/api/v6/{}", extension), "GET")
            .header("Host", "discordapp.com")
            .header("Authorization", fmt::format("Bot {}", token))
            .header("User-Agent", "DiscordBot (https://github.com/1whatleytay, 1, hello discord!)")
            .send(ssl);
        auto response = http::Response().receive(ssl);

        return utility::Json(std::string(response.body.begin(), response.body.end()));
    }

    Channel Client::getChannel(const Id &id) {
        return Channel(send(fmt::format("channels/{}", id.toString())));
    }

    Client::Client(std::string token) : token(std::move(token)) { }
}