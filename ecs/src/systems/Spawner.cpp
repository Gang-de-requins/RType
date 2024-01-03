#include "systems/Spawner.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void SpawnerSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();

        for (auto &event : scene.events.at(EventType::Spawn)) {
            if (event.event == Event::SpawnPlayerBullet) {
                // ecs::Entity &missile = sceneManager.createEntity(scene);

                // for (auto &entity : event.entities) {
                //     Position &position = sceneManager.get<Position>(*entity);
                //     Sprite &sprite = sceneManager.get<Sprite>(*entity);
                //     Scale &scale = sceneManager.get<Scale>(*entity);
                //     sceneManager.assign(missile, Position{position.x + sprite.source.width * scale.x, position.y + (sprite.source.height * scale.y) / 2});
                //     sceneManager.assign(missile, Velocity{6, 0});
                //     sceneManager.assign(missile, Sprite{"assets/28.png", Rectangle{0, 0, 210, 92}, Vector2{0, 0}});
                //     sceneManager.assign(missile, Acceleration{1, 0, 15});
                //     sceneManager.assign(missile, Scale{0.25, 0.25});
                //     sceneManager.assign(missile, Rotation{0});
                //     sceneManager.assign(missile, Collision{false, {}, true});
                //     sceneManager.assign(missile, Sound{"assets/weird.wav"});
                //     sceneManager.assign(missile, Damage{10});
                // }

                // scene.events[EventType::Audio].push_back({
                //     Event::PlaySound,
                //     {&missile}
                // });

                for (auto &entity : event.entities) {
                    this->spawnBullet(sceneManager, *entity, scene, true);
                }
            }

            event.entities.clear();
        }

        scene.events.at(EventType::Spawn).clear();
    }

    /* ------------------------- PRIVATE FUCNTIONS -------------------------- */

    void SpawnerSystem::spawnBullet(SceneManager &sceneManager, Entity &entity, Scene &scene, bool isPlayer) {
        Position &position = sceneManager.get<Position>(entity);
        Sprite &sprite = sceneManager.get<Sprite>(entity);
        Scale &scale = sceneManager.get<Scale>(entity);
        Entity &missile = sceneManager.createEntity(scene);

        sceneManager.assign(missile, isPlayer ?
            Position{position.x + sprite.source.width * scale.x, position.y + (sprite.source.height * scale.y) / 2}
            :
            Position{position.x - sprite.source.width * scale.x, position.y + (sprite.source.height * scale.y) / 2}
        );
        sceneManager.assign(missile, isPlayer ? Velocity{6, 0} : Velocity{-6, 0});
        sceneManager.assign(missile, Sprite{"assets/28.png", Rectangle{0, 0, 210, 92}, Vector2{0, 0}});
        sceneManager.assign(missile, Acceleration{1, 0, 15});
        sceneManager.assign(missile, Scale{0.25, 0.25});
        sceneManager.assign(missile, Rotation{0});
        sceneManager.assign(missile, Collision{false, {}, true});
        sceneManager.assign(missile, Sound{"assets/weird.wav"});
        sceneManager.assign(missile, Damage{10});

        scene.events[EventType::Audio].push_back({
            Event::PlaySound,
            {&missile}
        });
    }
}
