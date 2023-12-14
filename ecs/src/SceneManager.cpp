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
    
    void SceneManager::switchToScene(std::size_t sceneId) {
        this->m_currentSceneId = sceneId;
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

    Texture2D &SceneManager::getTexture(std::string_view path) {
        if (this->m_textures.find(path) == this->m_textures.end()) {
            this->m_textures.insert({path, LoadTexture(path.data())});
        }

        return this->m_textures.at(path);
    }

    ::Music &SceneManager::getMusic(std::string_view path) {
        if (this->m_musics.find(path) == this->m_musics.end()) {
            this->m_musics.insert({path, LoadMusicStream(path.data())});
        }

        return this->m_musics.at(path);
    }
}
