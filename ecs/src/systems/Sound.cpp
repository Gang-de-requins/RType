#include "systems/Sound.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void SoundSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Sound>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            auto &sound = sceneManager.get<Sound>(*entity);
            auto &soundData = sceneManager.getSound(sound.path);
            PlaySound(soundData);
        }
    }
}