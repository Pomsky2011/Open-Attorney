#include <SDL.h>
#include <iostream>
#include <filesystem>
#include "engine/init.h"
#include "script/loop.h"

namespace fs = std::filesystem;

fs::path getExecutableDir(const char* argv0) {
    fs::path executablePath = fs::absolute(argv0);
    return executablePath.parent_path();
}

int main(int argc, char* args[]) {
    fs::path executableDir = getExecutableDir(args[0]);
    std::cout << "Executable directory: " << executableDir << std::endl;

    GameState* state = init(argc, args, executableDir);
    if (state == nullptr) {
        std::cerr << "Failed to initialize!" << std::endl;
        return 1;
    }

    bool quit = false;
    movement_loop(state, quit);

    cleanup(state);

    return 0;
}