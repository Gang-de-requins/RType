# RType
> *This is an Epitech 3rd-year project.*

# GameEngine Documentation

## Table of contents
- [What is an ecs ?](#what-is-an-ecs-)
- [Components](#components)
- [Systems](#systems)
- [How to create a component](#how-to-create-a-component)
- [How to create a system](#how-to-create-a-system)
- [How to use the ecs](#how-to-use-the-ecs)
  - [Normal use](#normal-use)
  - [Use with JSON files](#use-with-json-files)

## What is an ecs ?

An Entity Component System is a design pattern that allows you to create entities and components that can be used in a game engine. <br>
The main idea is to create entities that are just a number, and components that are just data. <br>
The entities are stored in a vector for each scene, and the components are stored in a vector for each entity. <br>

## Components

| Component |
|-----------|
| Acceleration |
| Animation |
| Color |
| Controllable |
| FontSize |
| Music |
| Position |
| Rectangle |
| Rotation |
| Scale |
| Sprite|
| Text |
| Velocity |

## Systems

| Main System | Sub System |
|-------------|------------|
| Animation | |
| Controllable | |
| Movement | |
| Render | Text, Sprite |
| Music | |

## How to create a component

To create a component, you need to create a structure that contains the data you want to store. <br>
Include the component's file in the `include/Components.hpp` file. <br>
To add the new component from a JSON file, you need to create a function that parse a JSON object and add the component to the entity. Create this prototype in the `src/ParserJson.hpp` file and the function in the `src/ParserJson.cpp` file. <br>
Add the function in the `src/ParserJson.cpp` file in the `loadComponentsFromJson` function. <br>
You also need to add the component name to ALL_COMPONENTS in the `include/Macro.hpp` file.

```cpp
// include/components/Position.hpp
struct Position {
    float x;
    float y;
};

// ParserJson.hpp
void loadPosition(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &position);

// ParserJson.cpp
void loadPosition(SceneManager &sceneManager, Scene &scene, Entity &entity, rapidjson::Value &position)
{
    const std::array<std::string_view, 2> positionNames = {"x", "y"};

    for (const auto &positionName : positionNames) {
        if (!position.HasMember("x") || !position["x"].IsNumber()) {
            std::cerr << "Position has no " << positionName << " or is not a number in file: " << scene.path << std::endl;
            return;
        }
    }

    sceneManager.assign<Position>(entity, Position{position["x"].GetFloat(), position["y"].GetFloat()});
}
```

## How to create a system

To create a system, you need to create a class that inherits from the `ISystem` interface. <br>
Include the system's file in the `include/Systems.hpp` file. <br>

```cpp

// include/systems/Movement.hpp
#include <vector>
#include <algorithm>
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "ISystem.hpp"

namespace ecs {
    class SceneManager;

    class MovementSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
    };
}

// src/systems/Movement.cpp
#include "systems/Movement.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void MovementSystem::update(SceneManager &sceneManager) {
        std::vector<Entity *> entities = sceneManager.view<Position, Velocity, Acceleration>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            // Get the components
            Position &position = sceneManager.get<Position>(*entity);
            Velocity &velocity = sceneManager.get<Velocity>(*entity);
            Acceleration &acceleration = sceneManager.get<Acceleration>(*entity);

            velocity.dx += acceleration.ddx;
            velocity.dy += acceleration.ddy;

            velocity.dx = std::clamp(velocity.dx, -acceleration.maxSpeed, acceleration.maxSpeed);
            velocity.dy = std::clamp(velocity.dy, -acceleration.maxSpeed, acceleration.maxSpeed);

            position.x += velocity.dx;
            position.y += velocity.dy;
        }
    }
}
```

## How to use the ecs

### Normal use

To use the ecs, you need to create a `World` object. <br>

```cpp
#include "ecs/World.hpp"

int main()
{
    ecs::World world;
}
```

To create a scene, you need to call the `createScene` function. <br>

```cpp
#include "ecs/World.hpp"

int main()
{
    ecs::World world;
    ecs::Scene &scene = world.createScene("scene1");

    // Register the systems you want to use in the scene
    scene.registerSystems<ecs::MovementSystem>();
}
```

To create an entity, you need to call the `createEntity` function. <br>

```cpp
#include "ecs/World.hpp"

int main()
{
    ecs::World world;
    ecs::Scene &scene = world.createScene("scene1");
    ecs::Entity &entity = scene.createEntity();

    // Add components to the entity
    scene.assign<ecs::Position>(entity, ecs::Position{0, 0});
    scene.assign<ecs::Velocity>(entity, ecs::Velocity{0, 0});
    scene.assign<ecs::Acceleration>(entity, ecs::Acceleration{0, 0, 0});
}
```

To update the scene, you need to call the `update` function. <br>

```cpp
#include "ecs/World.hpp"

int main()
{
    ecs::World world;
    ecs::Scene &scene = world.createScene("scene1");
    ecs::Entity &entity = scene.createEntity();

    // Add components to the entity
    scene.assign<ecs::Position>(entity, ecs::Position{0, 0});
    scene.assign<ecs::Velocity>(entity, ecs::Velocity{0, 0});
    scene.assign<ecs::Acceleration>(entity, ecs::Acceleration{0, 0, 0});

    // Update the scene
    world.update();
}
```

### Use with JSON files

To load a entities for a scene from a JSON file, you need to set the `loadFromPath` variable to true and set the `path` variable to the path of the JSON file. <br>

```cpp
#include "ecs/World.hpp"

int main()
{
    ecs::World world;
    ecs::Scene &scene = world.createScene();

    scene.loadFromPath = true;
    scene.path = "path/to/file.json";
    world.switchToScene(scene.id);
}
```

The JSON file must be like this : <br>

```json
[
    {
        "components": [
            {
                "Position": {
                    "x": 0,
                    "y": 0
                }
            },
            {
                "Velocity": {
                    "dx": 0,
                    "dy": 0
                }
            },
            {
                "Acceleration": {
                    "ddx": 0,
                    "ddy": 0,
                    "maxSpeed": 0
                }
            }
        ]
    }
]
```
