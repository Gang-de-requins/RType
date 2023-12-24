#include "SceneManager.hpp"

namespace ecs {
    Scene &SceneManager::createScene() {
        this->m_scenes.emplace_back(Scene{this->m_nextSceneId++, {}, {}, "", false});
        return this->m_scenes.back();
    }
    
    void SceneManager::destroyScene(Scene &scene) {
        this->m_scenes.erase(std::remove_if(this->m_scenes.begin(), this->m_scenes.end(), [&scene](const Scene &s) {
            return s.id == scene.id;
        }), this->m_scenes.end());
    }

    void SceneManager::unloadScene(Scene &scene) {
        scene.entities.clear();
        scene.systems.clear();
    }
    
    void SceneManager::switchToScene(std::size_t sceneId) {
        std::cout << "Debut fonction de scene " << sceneId << std::endl;
        this->unloadScene(this->m_scenes.at(m_currentSceneId));

        this->m_nextEntityId = 0;
        this->m_currentSceneId = sceneId;
        std::cout << "currenSceneId " << this->m_currentSceneId << std::endl;
        if (this->m_scenes.at(m_currentSceneId).loadFromPath) {
            std::cout << "Je suis dans le if " << std::endl;
            this->loadEntitiesFromJson(this->m_scenes.at(m_currentSceneId));
        }
    }
    
    Scene &SceneManager::getCurrentScene() {
        return this->m_scenes[this->m_currentSceneId];
    }
    
    Entity &SceneManager::createEntity(Scene &scene) {
        scene.entities.emplace_back(Entity{this->m_nextEntityId++, {}});
        return scene.entities.back();
    }
    
    void SceneManager::destroyEntity(Scene &scene, Entity &entity) {
        scene.entities.erase(std::remove_if(scene.entities.begin(), scene.entities.end(), [&entity](const Entity &e) {
            return e.id == entity.id;
        }), scene.entities.end());
    }

    void SceneManager::update() {
        for (auto &system : this->m_scenes.at(this->m_currentSceneId).systems) {
            system->update(*this);
        }
    }

    void SceneManager::loadTextures(std::vector<std::string> &paths) {
        for (auto &path : paths) {
            this->getTexture(path);
        }
    }

    void SceneManager::loadMusics(std::vector<std::string> &paths) {
        for (auto &path : paths) {
            this->getMusic(path);
        }
    }

    void SceneManager::loadSounds(std::vector<std::string> &paths) {
        for (auto &path : paths) {
            this->getSound(path);
        }
    }

    Texture2D &SceneManager::getTexture(std::string path) {
        if (this->m_textures.find(path) == this->m_textures.end()) {
            this->m_textures.insert({path, LoadTexture(path.c_str())});
        }

        return this->m_textures.at(path);
    }

    ::Music &SceneManager::getMusic(std::string path) {
        if (this->m_musics.find(path) == this->m_musics.end()) {
            this->m_musics.insert({path, LoadMusicStream(path.c_str())});
        }

        return this->m_musics.at(path);
    }

    ::Sound &SceneManager::getSound(std::string path) {
        if (this->m_sounds.find(path) == this->m_sounds.end()) {
            this->m_sounds.insert({path, LoadSound(path.c_str())});
        }

        return this->m_sounds.at(path);
    }

    void SceneManager::loadEntitiesFromJson(Scene &scene) {
        ParserJson parserJson;

        parserJson.loadEntitiesFromJson(*this, scene);
    }
}
