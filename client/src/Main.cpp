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

    ecs::World engine;

    std::shared_ptr<ecs::MovementSystem> movementSystem = engine.addSystem<ecs::MovementSystem>();
    std::shared_ptr<ecs::RenderSpriteSystem> renderSpriteSystem = engine.addSystem<ecs::RenderSpriteSystem>();
    std::shared_ptr<ecs::RenderTextSystem> renderTextSystem = engine.addSystem<ecs::RenderTextSystem>();

    // Register components to MovementSystem
    engine.addComponentToSystem<ecs::MovementSystem, ecs::Position>();
    engine.addComponentToSystem<ecs::MovementSystem, ecs::Velocity>();

    // Register components to RenderSystem
    engine.addComponentToSystem<ecs::RenderSpriteSystem, ecs::Position>();
    engine.addComponentToSystem<ecs::RenderSpriteSystem, ecs::Sprite>();
    engine.addComponentToSystem<ecs::RenderSpriteSystem, ecs::Scale>();
    engine.addComponentToSystem<ecs::RenderSpriteSystem, ecs::Rect>();

    // Register components to RenderTextSystem
    engine.addComponentToSystem<ecs::RenderTextSystem, ecs::Position>();
    engine.addComponentToSystem<ecs::RenderTextSystem, ecs::Text>();
    engine.addComponentToSystem<ecs::RenderTextSystem, ecs::myColor>();
    engine.addComponentToSystem<ecs::RenderTextSystem, ecs::FontSize>();

    EntityID entity = engine.createEntity();

    engine.addComponentToEntity(entity, ecs::Position { 200.0f, 200.0f });
    engine.addComponentToEntity(entity, ecs::Velocity { .x = 0.0f, .y = 0.0f });
    engine.addComponentToEntity(entity, ecs::Scale { .x = 1.0f, .y = 1.0f });
    engine.addComponentToEntity(entity, ecs::Rect { .x = 0.0f, .y = 0.0f, .width = 32.0f, .height = 16.0f });
    engine.addComponentToEntity(entity, ecs::Sprite { .texture = LoadTexture("characters.gif"), .source = { 0.0f, 0.0f, 32.0f, 16.0f }, .origin = { 0.0f, 0.0f } });

    EntityID entity2 = engine.createEntity();

    engine.addComponentToEntity(entity2, ecs::Position { 180.0f, 180.0f });
    engine.addComponentToEntity(entity2, ecs::Velocity { 0.0f, 0.0f });
    engine.addComponentToEntity(entity2, ecs::Text { "Player 1" });
    engine.addComponentToEntity(entity2, ecs::myColor { .r = 255, .g = 255, .b = 255, .a = 255 });
    engine.addComponentToEntity(entity2, ecs::FontSize { .size = 20.0f });

    while (!WindowShouldClose()) {
        if (IsKeyDown(KEY_UP)) {
            engine.updateComponentToEntity(entity, ecs::Velocity { 0.0f, -2.0f });
            engine.updateComponentToEntity(entity2, ecs::Velocity { 0.0f, -2.0f });
        } else if (IsKeyDown(KEY_DOWN)) {
            engine.updateComponentToEntity(entity, ecs::Velocity { 0.0f, 2.0f });
            engine.updateComponentToEntity(entity2, ecs::Velocity { 0.0f, 2.0f });
        } else if (IsKeyDown(KEY_LEFT)) {
            engine.updateComponentToEntity(entity, ecs::Velocity { -2.0f, 0.0f });
            engine.updateComponentToEntity(entity2, ecs::Velocity { -2.0f, 0.0f });
        } else if (IsKeyDown(KEY_RIGHT)) {
            engine.updateComponentToEntity(entity, ecs::Velocity { 2.0f, 0.0f });
            engine.updateComponentToEntity(entity2, ecs::Velocity { 2.0f, 0.0f });
        } else {
            engine.updateComponentToEntity(entity, ecs::Velocity { 0.0f, 0.0f });
            engine.updateComponentToEntity(entity2, ecs::Velocity { 0.0f, 0.0f });
        }

        BeginDrawing();

        ClearBackground(BLACK);

        movementSystem->update();
        renderSpriteSystem->update();
        renderTextSystem->update();

        EndDrawing();
    }

    return EXIT_SUCCESS;
}
