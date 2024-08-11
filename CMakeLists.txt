cmake_minimum_required(VERSION 3.10)
   project(OpenAttorney)
   
   set(CMAKE_CXX_STANDARD 11)
   set(CMAKE_CXX_STANDARD_REQUIRED True)

   find_package(SDL2 REQUIRED)
   include_directories(${SDL2_INCLUDE_DIRS})
   include_directories(${CMAKE_SOURCE_DIR})
   
   add_executable(OpenAttorney 
       main.cpp
       engine/init.cpp
   )
   
   target_link_libraries(OpenAttorney ${SDL2_LIBRARIES})
