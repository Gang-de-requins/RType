#include "systems/Music.hpp"
#include "World.hpp"

namespace ecs {
    class World;

    void MusicSystem::update(World &world) {
        auto entities = world.view<Music>();

        for (auto &entity : entities) {
            auto &music = world.get<Music>(*entity);
            auto &musicData = world.getMusic(music.path);

            IsMusicStreamPlaying(musicData) ? UpdateMusicStream(musicData) : PlayMusicStream(musicData);
        }
    }
}
