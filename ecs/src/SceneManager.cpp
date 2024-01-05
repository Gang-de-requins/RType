#include "SceneManager.hpp"

namespace ecs {
    Scene &SceneManager::createScene() {
        this->m_scenes.emplace_back(Scene{this->m_nextSceneId++, 0, {}, {}, {
            {EventType::Collisionnnnnn, {}},
            {EventType::Destroy, {}},
            {EventType::Input, {}},
            {EventType::Spawn, {}},
            {EventType::Timer, {}},
            {EventType::Audio, {}}
        }, "", false});
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
        scene.events.clear();
        scene.nextEntityId = 0;
    }
    
    void SceneManager::switchToScene(std::size_t sceneId) {
        this->unloadScene(this->m_scenes.at(this->m_currentSceneId));

        this->m_currentSceneId = sceneId;
        if (this->m_scenes.at(this->m_currentSceneId).loadFromPath) {
            this->loadEntitiesFromJson(this->m_scenes.at(this->m_currentSceneId));
        }
    }
    
    Scene &SceneManager::getCurrentScene() {
        return this->m_scenes.at(this->m_currentSceneId);
    }
    
    Entity &SceneManager::createEntity(Scene &scene) {
        scene.entities.emplace_back(Entity{scene.nextEntityId++, {}});
        return scene.entities.back();
    }
    
    void SceneManager::destroyEntity(Scene &scene, Entity &entity) {
        scene.entities.erase(std::remove_if(scene.entities.begin(), scene.entities.end(), [&entity](const Entity &e) {
            return e.id == entity.id;
        }), scene.entities.end());
    }

    Entity &SceneManager::getEntityById(Scene &scene, std::size_t id) {
        return *std::find_if(scene.entities.begin(), scene.entities.end(), [&id](const Entity &e) {
            return e.id == id;
        });
    }

    void SceneManager::update() {
        ecs::Scene &scene = this->getCurrentScene();

        for (auto &system : this->m_scenes.at(this->m_currentSceneId).systems) {
            if (scene != this->getCurrentScene())
                break;
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
