#include "Game.hpp"

namespace Client {
    Game::Game() {
        InitWindow(800, 450, "rtype");
        SetTargetFPS(60);
    }

    Game::~Game()
    {}

    int Game::launchGame(void) {
        ecs::Entity &entity = this->_ecs.createEntity();

        while (!WindowShouldClose()) {
            BeginDrawing();
            ClearBackground(BLACK);

            _movementSystem.update();
            _controllableSystem.update();
            _spriteSystem.update();
            _animationSystem.update();
            _musicSystem.update();
            _textSystem.update();

            EndDrawing();
        }
        CloseWindow();
        return (0);
    }
}
