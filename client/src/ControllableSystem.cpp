#include "ControllableSystem.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void ControllableSystem::update(SceneManager &sceneManager) {
        Scene &scene = sceneManager.getCurrentScene();

        for (auto &event : scene.events.at(EventType::KeyboardInput)) {
            if (event.event == Event::KEY_W || event.event == Event::KEY_UP) {
                scene.events[EventType::Input].push_back({
                    Event::MoveUp,
                    {event.entities.at(0)}
                });
            }
            if (event.event == Event::KEY_S || event.event == Event::KEY_DOWN) {
                scene.events[EventType::Input].push_back({
                    Event::MoveDown,
                    {event.entities.at(0)}
                });
            }
            if (event.event == Event::KEY_A || event.event == Event::KEY_LEFT) {
                scene.events[EventType::Input].push_back({
                    Event::MoveLeft,
                    {event.entities.at(0)}
                });
            }
            if (event.event == Event::KEY_D || event.event == Event::KEY_RIGHT) {
                scene.events[EventType::Input].push_back({
                    Event::MoveRight,
                    {event.entities.at(0)}
                });
            }
            if (event.event == Event::KEY_SPACE) {
                scene.events[EventType::Spawn].push_back({
                    Event::SpawnPlayerBullet,
                    {event.entities.at(0)}
                });
            }
        }
    }
}
