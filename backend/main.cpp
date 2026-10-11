#include "Game.h"
#include <httplib.h>
#include <nlohmann/json.hpp>
#include <iostream>

using nlohmann::json;

int main() {
    Game game;
    httplib::Server server;

    server.Get("/api/health", [](const httplib::Request&, httplib::Response& response) {
        response.set_content(R"({"ok":true,"name":"Secrets of Ravenwood"})", "application/json");
    });

    server.Get("/api/state", [&game](const httplib::Request&, httplib::Response& response) {
        response.set_content(game.getState().dump(), "application/json");
    });

    server.Post("/api/action", [&game](const httplib::Request& request, httplib::Response& response) {
        try {
            const json body = json::parse(request.body);
            response.set_content(game.performAction(body).dump(), "application/json");
        } catch (const json::exception&) {
            response.status = 400;
            response.set_content(R"({"error":"Request body must be valid JSON."})", "application/json");
        }
    });

    server.set_mount_point("/", RAVENWOOD_FRONTEND_DIR);
    std::cout << "Secrets of Ravenwood running at http://localhost:8080\n"
              << "Keep this terminal open while playing. Press Ctrl+C to stop.\n";

    if (!server.listen("127.0.0.1", 8080)) {
        std::cerr << "Could not start on port 8080. Check whether another program is using it.\n";
        return 1;
    }
    return 0;
}
