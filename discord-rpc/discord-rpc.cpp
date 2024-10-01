#include <iostream>
#include <string.h>
#include "discord_rpc.h"
#include <chrono>
#include <thread>
#include <string>

void handleDiscordError(int errcode, const char* message) {
    std::cerr << "Something went wrong [" << errcode << "]: " << message << std::endl;
}

void init(const char* appId) {
    std::cout << "Developed by AroliSG. All rights reserved." << std::endl << std::flush;
    std::cout << "Type 'q' to quit." << std::endl << std::flush;

    DiscordEventHandlers handlers;

    memset(&handlers, 0, sizeof(handlers));
    Discord_Initialize(appId, &handlers, 1, NULL);

    handlers.errored = handleDiscordError;

    std::cout << "RPC Initiliazed with appId: " << appId << std::endl << std::flush;
}

void updatePresence(
    const char* state,
    const char* details,
    const char* lUrl,
    const char* lTitle,
    const char* mUrl,
    const char* mTitle
) {
    DiscordRichPresence discordPresence;
    memset(&discordPresence, 0, sizeof(discordPresence));

    discordPresence.state = state;
    discordPresence.details = details;
    discordPresence.largeImageKey = lUrl;
    discordPresence.largeImageText = lTitle;
    discordPresence.smallImageKey = mUrl;
    discordPresence.smallImageText = mTitle;


    discordPresence.startTimestamp = time(0);

    Discord_UpdatePresence(&discordPresence);

    std::cout << "Presence running." << std::endl << std::flush;
}

void runLoop() {
    std::string input;

    while (true) {
        Discord_RunCallbacks();

        if (std::cin.peek() != EOF) {
            std::getline(std::cin, input);
            if (input == "q") {
                std::cout << "Shutting down..." << std::endl << std::flush;
                break;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
}

int main(int argc, char* argv[]) {
    try {
        if (argc < 8) {
            std::cerr << "Usage: discord-rpc.exe <title> <details> <Image url> <Image title> <Image url> <Image title>" << std::endl << std::flush;
            return 1;
        }

        init(argv[1]);

        char* mediumTitle = argv[6];
        if (argv[6] == "null") {
            mediumTitle = NULL;
        }

        char* mediumURL = argv[7];
        if (argv[7] == "null") {
            mediumURL = NULL;
        }

        updatePresence(
            argv[2],
            argv[3],
            argv[4],
            argv[5],
            mediumTitle,
            mediumURL
        );
        runLoop();

        std::cout << "Shutting down Discord RPC..." << std::endl << std::flush;
        Discord_Shutdown();

        std::cout << "Discord RPC shut down." << std::endl << std::flush;
    }
    catch (const std::exception& e) {
        std::cerr << "Unexpected error: " << e.what() << std::endl;
        return 1;
    }

    return 0;

}
