#include <SDL.h>
#include <iostream>
#include "engine/init.h"
#include "engine/texture_loader.h"
#include "script/loop.h"
#include "engine/appdata.h"

int main(int argc, char* args[]) {
    std::cout << "Open Attorney\nThis program comes with ABSOLUTELY NO WARRANTY; for details visit https://www.gnu.org/licenses/.\nThis is free software, and you are welcome to redistribute it\nunder certain conditions; visit https://www.gnu.org/licenses/ for details.\n";
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