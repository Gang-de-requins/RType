#include "systems/Sound.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void SoundSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();
        int index = 0;
        std::vector<int> eventsToRemove = {};

        for (auto &event : scene.events.at(EventType::Audio)) {
            switch (event.event) {
                case Event::PlaySound:
                    for (auto &entity : event.entities) {
                        Sound &sound = sceneManager.get<Sound>(*entity);
                        sf::Sound &soundData = sceneManager.getSound(sound.path);

                        soundData.play();
                    }
                    eventsToRemove.push_back(index);
                    break;
                default:
                    break;
            }
            index++;
        }

        for (auto &event : eventsToRemove) {
            scene.events.at(EventType::Audio).erase(scene.events.at(EventType::Audio).begin() + event);

            for (auto &i : eventsToRemove) {
                if (i > event) {
                    i--;
                }
            }
        }
    }
}