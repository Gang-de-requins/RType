#include "Game.hpp"

namespace Client {
    Game::Game() {
        InitWindow(800, 450, "rtype");
        SetTargetFPS(60);
    }

    Game::~Game()
    {}

    int Game::launchGame(void) {
        while (!WindowShouldClose()) {
            BeginDrawing();

            ClearBackground(RAYWHITE);

            DrawText("Salut, c'est Raylib !", 10, 10, 20, DARKGRAY);

            EndDrawing();
        }
        CloseWindow();
        return (0);
    }
}
