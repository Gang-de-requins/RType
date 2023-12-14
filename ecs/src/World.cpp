#include "World.hpp"

namespace ecs {

    Scene &World::createScene() {
        return this->m_sceneManager.createScene();
    }

    void World::destroyScene(Scene &scene) {
        this->m_sceneManager.destroyScene(scene);
    }
    
    void World::switchToScene(std::size_t sceneId) {
        this->m_sceneManager.switchToScene(sceneId);
    }

    Scene &World::getCurrentScene() {
        return this->m_sceneManager.getCurrentScene();
    }

    Entity &World::createEntity(Scene &scene) {
        return this->m_sceneManager.createEntity(scene);
    }

    void World::destroyEntity(Scene &scene, Entity &entity) {
        this->m_sceneManager.destroyEntity(scene, entity);
    }

    // Entity &World::createEntity() {
    //     this->m_entities.emplace_back(Entity{this->m_nextEntityId++, {}});
    //     return this->m_entities.back();
    // }

    // void World::destroyEntity(Entity &entity) {
    //     this->m_entities.erase(std::remove_if(this->m_entities.begin(), this->m_entities.end(), [&entity](const Entity &e) {
    //         return e.id == entity.id;
    //     }), this->m_entities.end());
    // }

    // Texture2D &World::getTexture(std::string_view path) {
    //     if (this->m_textures.find(path) == this->m_textures.end()) {
    //         this->m_textures.insert({path, LoadTexture(path.data())});
    //     }

    //     return this->m_textures.at(path);
    // }

    // ::Music &World::getMusic(std::string_view path) {
    //     if (this->m_musics.find(path) == this->m_musics.end()) {
    //         this->m_musics.insert({path, LoadMusicStream(path.data())});
    //     }

    //     return this->m_musics.at(path);
    // }
}
