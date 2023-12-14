#include <iostream>
#include "GameEngine.hpp"
#include "Game.hpp"

int main(int ac, char **av) {
    Client::Game gameClient;
    gameClient.launchGame();
    return (0);
}

// int main(void)
// {
//     ecs::World world;

//     ecs::MovementSystem movementSystem;
//     ecs::ControllableSystem controllableSystem;
//     ecs::SpriteSystem spriteSystem;
//     ecs::AnimationSystem animationSystem;
//     ecs::MusicSystem musicSystem;
//     ecs::TextSystem textSystem;

//     ecs::Entity &entity = world.createEntity();
//     ecs::Position position{200, 200};
//     ecs::Velocity velocity{0, 0};
//     ecs::Sprite sprite{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}};
//     ecs::Acceleration acceleration{0, 0, 4};
//     ecs::Controllable controllable{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
//     ecs::Scale scale{1, 1};
//     ecs::Rotation rotation{0};
//     ecs::Animation animation{ecs::Rectangle{0, 0, 32, 0}, 4, 0, 200, std::chrono::steady_clock::now()};

//     world.assign(entity, position);
//     world.assign(entity, velocity);
//     world.assign(entity, sprite);
//     world.assign(entity, acceleration);
//     world.assign(entity, controllable);
//     world.assign(entity, scale);
//     world.assign(entity, rotation);
//     world.assign(entity, animation);

//     ecs::Entity &entity1 = world.createEntity();
//     ecs::Position position1{180, 180};
//     ecs::Velocity velocity1{0, 0};
//     ecs::Text text{"Player 1"};
//     ecs::Acceleration acceleration1{0, 0, 4};
//     ecs::Controllable controllable1{KEY_UP, KEY_DOWN, KEY_LEFT, KEY_RIGHT};
//     ecs::Color color{GE_WHITE};
//     ecs::FontSize fontSize{ 20 };

//     world.assign(entity1, position1);
//     world.assign(entity1, velocity1);
//     world.assign(entity1, text);
//     world.assign(entity1, acceleration1);
//     world.assign(entity1, controllable1);
//     world.assign(entity1, color);
//     world.assign(entity1, fontSize);

//     ecs::Entity &entity2 = world.createEntity();
//     ecs::Position position2{400, 200};
//     ecs::Velocity velocity2{0, 0};
//     ecs::Sprite sprite2{"assets/characters.gif", ecs::Rectangle{0, 0, 32, 16}, ecs::Vector2{0, 0}};
//     ecs::Acceleration acceleration2{0, 0, 4};
//     ecs::Controllable controllable2{KEY_W, KEY_S, KEY_A, KEY_D};
//     ecs::Scale scale2{1, 1};
//     ecs::Rotation rotation2{0};

//     world.assign(entity2, position2);
//     world.assign(entity2, velocity2);
//     world.assign(entity2, sprite2);
//     world.assign(entity2, acceleration2);
//     world.assign(entity2, controllable2);
//     world.assign(entity2, scale2);
//     world.assign(entity2, rotation2);

//     ecs::Entity &entity3 = world.createEntity();
//     ecs::Music music{"assets/mini1111.xm"};

//     world.assign(entity3, music);

//     InitAudioDevice();
//     InitWindow(800, 450, "rtype");
//     SetTargetFPS(60);

//     while (!WindowShouldClose())
//     {
//         BeginDrawing();
//         ClearBackground(BLACK);

//         musicSystem.update(world);
//         controllableSystem.update(world);
//         movementSystem.update(world);
//         animationSystem.update(world);
//         spriteSystem.update(world);
//         textSystem.update(world);

//         EndDrawing();
//     }

//     CloseWindow();
//     CloseAudioDevice();

//     return EXIT_SUCCESS;
// }
