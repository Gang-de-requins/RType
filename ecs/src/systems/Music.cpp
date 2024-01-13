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
                    scene.events[EventType::Audio].push_back({
                        Event::PlayMusic,
                        {entity}
                    });
                    checkAllMusic = false;
                }
            }
        }

        for (auto &event : scene.events.at(EventType::Audio)) {
            switch (event.event) {
                case Event::PlayMusic:
                    for (auto &entity : event.entities) {
                        Music &music = sceneManager.get<Music>(*entity);
                        // sf::Music &musicData = sceneManager.getMusic(music.path);

                        // PlayMusicStream(musicData);

                        // musicData.setLoop(true);
                        // musicData.setVolume(music.volume);
                        // musicData.play();

                        // if (true) {
                        //     entitiesUpdateEvent.push_back(entity);
                        // }
                    }
                    eventsToRemove.push_back(index);
                    break;
                case Event::StopMusic:
                    // for (auto &entity : event.entities) {
                    //     Music &music = sceneManager.get<Music>(*entity);
                    //     sf::Music &musicData = sceneManager.getMusic(music.path);

                    //     // StopMusicStream(musicData);

                    //     musicData.stop();
                    // }
                    eventsToRemove.push_back(index);
                    break;
                case Event::PauseMusic:
                    // for (auto &entity : event.entities) {
                    //     Music &music = sceneManager.get<Music>(*entity);
                    //     ::Music &musicData = sceneManager.getMusic(music.path);

                    //     // PauseMusicStream(musicData);

                    //     musicData.pause();
                    // }
                    eventsToRemove.push_back(index);
                    break;
                case Event::ResumeMusic:
                    // for (auto &entity : event.entities) {
                    //     Music &music = sceneManager.get<Music>(*entity);
                    //     ::Music &musicData = sceneManager.getMusic(music.path);

                    //     // ResumeMusicStream(musicData);

                    //     musicData.play();
                    // }
                    eventsToRemove.push_back(index);
                    break;
                case Event::UpdateMusic:
                    // for (auto &entity : event.entities) {
                    //     Music &music = sceneManager.get<Music>(*entity);
                    //     ::Music &musicData = sceneManager.getMusic(music.path);

                    //     // IsMusicStreamPlaying(musicData) ? UpdateMusicStream(musicData) : PlayMusicStream(musicData);

                    //     entitiesUpdateEvent.push_back(entity);
                    // }
                    eventsToRemove.push_back(index);
                    break;
                case Event::SetVolumeMusic:
                    // for (auto &entity : event.entities) {
                    //     Music &music = sceneManager.get<Music>(*entity);
                    //     ::Music &musicData = sceneManager.getMusic(music.path);

                    //     SetMusicVolume(musicData, music.volume);
                    // }
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

        for (auto &entity : entitiesUpdateEvent) {
            scene.events[EventType::Audio].push_back({
                Event::UpdateMusic,
                {entity}
            });
        }
    }
}
