cmake_minimum_required(VERSION 3.10)
project(OpenAttorney)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

find_package(SDL2 REQUIRED)
find_package(Python3 REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS})
include_directories(${CMAKE_SOURCE_DIR})

add_executable(OpenAttorney 
    main.cpp
    engine/init.cpp
    engine/appdata.cpp
    engine/texture_loader.cpp
    engine/asset_manager.cpp
    script/loop.cpp
)

target_link_libraries(OpenAttorney ${SDL2_LIBRARIES})

if(APPLE)
    target_link_libraries(OpenAttorney "-framework CoreFoundation")
endif()

# Add custom target to run Python script
add_custom_target(append_asset
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/OAAA_Append.py
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Appending Assets"
)

# Make sure OpenAttorney target depends on append_asset
add_dependencies(OpenAttorney append_asset)