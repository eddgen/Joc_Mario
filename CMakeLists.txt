cmake_minimum_required(VERSION 3.16)
project(Joc_Mario)

set(CMAKE_CXX_STANDARD 20)

# Set path to SFML
set(SFML_DIR C:/SFML-2.6.2/lib/cmake/SFML)

# Find SFML
find_package(SFML 2.6 COMPONENTS graphics window system REQUIRED)

# Add Box2D
add_subdirectory(box2d)

# Add source files
add_executable(Joc_Mario
        main.cpp
        Game.cpp
        Game.h
        Camera.cpp
        Camera.h
        Renderer.cpp
        Renderer.h
        Resources.cpp
        Resources.h
        Map.cpp
        Map.h
        Player.cpp
        Player.h
        Physics.cpp
        Physics.h
        Animation.cpp
        Animation.h
        AnimationV2.cpp
        AnimationV2.h
        object.h
        Coin.cpp
        Coin.h
        Enemy.cpp
        Enemy.h
)

# Link SFML and Box2D
target_link_libraries(Joc_Mario PRIVATE sfml-graphics sfml-window sfml-system sfml-audio box2d)

# Include Box2D headers
target_include_directories(Joc_Mario PRIVATE
        ${CMAKE_SOURCE_DIR}/box2d/include
)

# Copy resources to build directory
file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})