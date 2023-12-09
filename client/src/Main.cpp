#include <iostream>
#include "raylib.h"
#include "Core.hpp"

int main(void)
{
    std::cout << "Project Client" << std::endl;

    const int screenWidth = 800;
    const int screenHeight = 450;

    InitWindow(screenWidth, screenHeight, "Project Client");

    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        BeginDrawing();

        ClearBackground(RAYWHITE);

        DrawText("Project Client", 190, 200, 20, LIGHTGRAY);

        EndDrawing();
    }

    return EXIT_SUCCESS;
}
