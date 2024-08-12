# Open Attorney

An open-source SDL Ace Attorney Engine licensed under GPLv3.

## Project Overview

Open Attorney aims to create an open-source engine for Ace Attorney-style games using SDL2. The project is in its early stages, focusing on basic functionality and laying the groundwork for future features.

## Current Features

- SDL2 window creation and management
- Sprite rendering and movement
- Window scaling with maintained 4:3 aspect ratio
- Basic error handling and debugging output

## Dependencies

- SDL2 (Latest version)
- C++17 compatible compiler

## Project Structure

```
Open Attorney/
├── main.cpp
├── engine/
│   ├── init.cpp
│   ├── init.h
│   ├── appdata.cpp
│   ├── appdata.h
│   ├── texture_loader.cpp
│   └── texture_loader.h
├── script/
│   ├── loop.cpp
│   └── loop.h
└── CMakeLists.txt
```

## Building the Project

### Using Visual Studio Code (Recommended)

1. Clone or download this repository.
2. Open the project folder in Visual Studio Code.
3. Install the C/C++ and CMake extensions.
4. Configure the project using CMake.
5. Build the project using the CMake extension or the provided tasks in `.vscode/tasks.json`.

### Manual Compilation

If not using VS Code, you can compile manually using the following command:

```bash
clang++ -std=c++17 -stdlib=libc++ -g main.cpp engine/init.cpp engine/appdata.cpp engine/texture_loader.cpp script/loop.cpp -o main -I. -I/usr/local/opt/sdl2/include/SDL2 -L/usr/local/opt/sdl2/lib -lSDL2
```

Note: Adjust the SDL2 include and library paths as necessary for your system.

## Current Functionality

- Opens a window with a 4:3 aspect ratio gameplay area.
- Renders a sprite (sprite.bmp) that can be moved using arrow keys.
- Handles window resizing while maintaining the aspect ratio.
- Implements basic error handling and logging.

## Immediate Goals

1. Implement a title screen.
2. Create a loading animation.

## Future Plans

1. Implement the witness stand and courtroom mechanics.
2. Develop a case creation system.
3. Add support for investigations.
4. Create a custom .cas file format for Open Attorney cases.
5. Implement compatibility with official Ace Attorney game assets (for non-pirated copies).

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.

## License

This project is licensed under the GNU General Public License v3.0 (GPLv3).
