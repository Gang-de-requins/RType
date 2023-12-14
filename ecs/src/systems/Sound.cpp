#include "systems/Sound.hpp"
#include "World.hpp"

namespace ecs {
    class World;

    void SoundSystem::update(World &world) {
        auto entities = world.view<Sound>();

        for (auto &entity : entities) {
            auto &sound = world.get<Sound>(*entity);
            auto &soundData = world.getSound(sound.path);

            if (IsSoundPlaying(soundData))
                PlaySound(soundData);
        }
    }
}