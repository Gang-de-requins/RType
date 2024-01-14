#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <algorithm>
#include <string>
#include "raylib.h"

namespace ecs {
    class assetsManager {
        std::unordered_map<std::string, Texture2D> m_textures; // Textures
        std::unordered_map<std::string, ::Music> m_musics; // Musics
        std::unordered_map<std::string, ::Sound> m_sounds; // Sounds

        public:

            /**
             * @fn SceneManager::getTexture
             * @brief Get a texture
             * 
             * @param path The path to the texture.
             * @return The texture.
             */
            Texture2D &getTexture(std::string path) {
                if (this->m_textures.find(path) == this->m_textures.end()) {
                    this->m_textures.insert({path, LoadTexture(path.c_str())});
                }

                return this->m_textures.at(path);
            }

            /**
             * @fn SceneManager::getMusic
             * @brief Get a music
             * 
             * @param paths The path to the music.
             * @return The music.
             */
            ::Music &getMusic(std::string path) {
                if (this->m_musics.find(path) == this->m_musics.end()) {
                    this->m_musics.insert({path, LoadMusicStream(path.c_str())});
                }

                return this->m_musics.at(path);
            }

            /**
             * @fn SceneManager::getSound
             * @brief Get a sound
             * 
             * @param path The path to the sound.
             * @return The sound.
             */
            ::Sound &getSound(std::string path) {
                if (this->m_sounds.find(path) == this->m_sounds.end()) {
                    this->m_sounds.insert({path, LoadSound(path.c_str())});
                }

                return this->m_sounds.at(path);
            }

            /**
             * @fn SceneManager::loadTextures
             * @brief Load textures
             * 
             * @param path The path to the textures.
             */
            void loadTextures(std::vector<std::string> &paths) {
                for (auto &path : paths) {
                    this->getTexture(path);
                }
            }

            /**
             * @fn SceneManager::loadMusics
             * @brief Load musics
             * 
             * @param paths The paths to the musics.
             */
            void loadMusics(std::vector<std::string> &paths) {
                for (auto &path : paths) {
                    this->getMusic(path);
                }
            }

            /**
             * @fn SceneManager::loadSounds
             * @brief Load sounds
             * 
             * @param paths The paths to the sounds.
             */
            void loadSounds(std::vector<std::string> &paths) {
                for (auto &path : paths) {
                    this->getSound(path);
                }
            }
    };
}

#endif