#include <SDL.h>
#include <iostream>
#include "engine/init.h"
#include "script/loop.h"
#include "engine/appdata.h"

int main(int argc, char* args[]) {
    try {
        // Initialize AppData and copy assets if necessary
        appdata::initializeAssets();

        GameState* state = init(argc, args);
        if (state == nullptr) {
            throw std::runtime_error("Failed to initialize game state!");
        }

        bool quit = false;
        movement_loop(state, quit);

        cleanup(state);

        return 0;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }
}