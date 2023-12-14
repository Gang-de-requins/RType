#include "systems/Music.hpp"
#include "SceneManager.hpp"

namespace ecs {
    class SceneManager;

    void MusicSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Music>(sceneManager.getCurrentScene());

        for (auto &entity : entities) {
            auto &music = sceneManager.get<Music>(*entity);
            auto &musicData = sceneManager.getMusic(music.path);

            IsMusicStreamPlaying(musicData) ? UpdateMusicStream(musicData) : PlayMusicStream(musicData);
        }
    }
}
