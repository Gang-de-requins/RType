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

    SceneManager &World::getSceneManager() {
        return this->m_sceneManager;
    }

    Entity &World::createEntity(Scene &scene) {
        return this->m_sceneManager.createEntity(scene);
    }

    void World::destroyEntity(Scene &scene, Entity &entity) {
        this->m_sceneManager.destroyEntity(scene, entity);
    }

    void World::update() {
        this->m_sceneManager.update();
    }

    void World::loadTextures(std::vector<std::string> paths) {
        this->m_sceneManager.loadTextures(paths);
    }

    void World::loadMusics(std::vector<std::string> paths) {
        this->m_sceneManager.loadMusics(paths);
    }

    void World::loadSounds(std::vector<std::string> paths) {
        this->m_sceneManager.loadSounds(paths);
    }
}
