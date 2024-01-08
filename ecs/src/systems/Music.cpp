#include "systems/Music.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void MusicSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();
        int index = 0;
        std::vector<int> eventsToRemove = {};
        std::vector<Entity *> entitiesUpdateEvent = {};
        static bool checkAllMusic = true;

        if (checkAllMusic) {
            for (auto &entity : sceneManager.view<Music>(scene)) {
                Music &music = sceneManager.get<Music>(*entity);

                if (music.toPlayAtStart) {
                    music.toPlayAtStart = false;
                    scene.events[DefaultEventType::Audio].push_back({
                        DefaultEvent::PlayMusic,
                        {entity}
                    });
                    checkAllMusic = false;
                }
            }
        }

        for (auto &event : scene.events.at(DefaultEventType::Audio)) {
            switch (event.event) {
                case DefaultEvent::PlayMusic:
                    for (auto &entity : event.entities) {
                        Music &music = sceneManager.get<Music>(*entity);
                        ::Music &musicData = sceneManager.getMusic(music.path);

                        PlayMusicStream(musicData);
                        
                        if (musicData.looping) {
                            entitiesUpdateEvent.push_back(entity);
                        }
                    }
                    eventsToRemove.push_back(index);
                    break;
                case DefaultEvent::StopMusic:
                    for (auto &entity : event.entities) {
                        Music &music = sceneManager.get<Music>(*entity);
                        ::Music &musicData = sceneManager.getMusic(music.path);

                        StopMusicStream(musicData);
                    }
                    eventsToRemove.push_back(index);
                    break;
                case DefaultEvent::PauseMusic:
                    for (auto &entity : event.entities) {
                        Music &music = sceneManager.get<Music>(*entity);
                        ::Music &musicData = sceneManager.getMusic(music.path);

                        PauseMusicStream(musicData);
                    }
                    eventsToRemove.push_back(index);
                    break;
                case DefaultEvent::ResumeMusic:
                    for (auto &entity : event.entities) {
                        Music &music = sceneManager.get<Music>(*entity);
                        ::Music &musicData = sceneManager.getMusic(music.path);

                        ResumeMusicStream(musicData);
                    }
                    eventsToRemove.push_back(index);
                    break;
                case DefaultEvent::UpdateMusic:
                    for (auto &entity : event.entities) {
                        Music &music = sceneManager.get<Music>(*entity);
                        ::Music &musicData = sceneManager.getMusic(music.path);

                        IsMusicStreamPlaying(musicData) ? UpdateMusicStream(musicData) : PlayMusicStream(musicData);

                        entitiesUpdateEvent.push_back(entity);
                    }
                    eventsToRemove.push_back(index);
                    break;
                case DefaultEvent::SetVolumeMusic:
                    for (auto &entity : event.entities) {
                        Music &music = sceneManager.get<Music>(*entity);
                        ::Music &musicData = sceneManager.getMusic(music.path);

                        SetMusicVolume(musicData, music.volume);
                    }
                    eventsToRemove.push_back(index);
                    break;
                default:
                    break;
            }
            index++;
        }

        for (auto &event : eventsToRemove) {
            scene.events.at(DefaultEventType::Audio).erase(scene.events.at(DefaultEventType::Audio).begin() + event);
        }

        for (auto &entity : entitiesUpdateEvent) {
            scene.events[DefaultEventType::Audio].push_back({
                DefaultEvent::UpdateMusic,
                {entity}
            });
        }
    }
}
