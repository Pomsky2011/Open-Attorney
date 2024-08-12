#include <SDL.h>
#include <iostream>
#include "engine/init.h"
#include "engine/texture_loader.h"
#include "script/loop.h"
#include "engine/appdata.h"

int main(int argc, char* args[]) {
    try {
        std::cout << "Open Attorney" << std::endl;
        std::cout << "This program comes with ABSOLUTELY NO WARRANTY; for details visit https://www.gnu.org/licenses/." << std::endl;
        std::cout << "This is free software, and you are welcome to redistribute it under certain conditions; visit https://www.gnu.org/licenses/ for details." << std::endl;

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
        std::cerr << "Fatal error: " << e.what() << std::endl;
        return 1;
    }
}