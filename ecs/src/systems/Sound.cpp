#include "systems/Sound.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void SoundSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();

        for (auto &event : scene.events.at(EventType::Audio)) {
            switch (event.event) {
                case Event::PlaySound:
                    for (auto &entity : event.entities) {
                        Sound &sound = sceneManager.get<Sound>(*entity);
                        ::Sound &soundData = sceneManager.getSound(sound.path);

                        ::PlaySound(soundData);
                    }
                    break;
                default:
                    break;
            }

            event.entities.clear();
        }

        scene.events.at(EventType::Audio).clear();
    }
}