#include "SceneManager.hpp"

namespace ecs {
    Scene &SceneManager::createScene() {
        this->m_scenes.emplace_back(Scene{this->m_nextSceneId++, 0, {}, {}, {
            {EventType::Collisionnnnnn, {}},
            {EventType::Destroy, {}},
            {EventType::Input, {}},
            {EventType::Spawn, {}},
            {EventType::Timer, {}},
            {EventType::Audio, {}},
            {EventType::KeyboardInput, {}}
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

    Scene &SceneManager::getSceneById(std::size_t id) {
        return *std::find_if(m_scenes.begin(), m_scenes.end(), [&id](const Scene &e) {
            return e.id == id;
        });
    }

    void SceneManager::emit(Scene &scene, int eventType, int event, std::vector<Entity *> entities) {
		scene.events[eventType].push_back({event, entities});
    }

    void SceneManager::update() {
        ecs::Scene &scene = this->getCurrentScene();

        for (auto &system : this->m_scenes.at(this->m_currentSceneId).systems) {
            if (scene != this->getCurrentScene())
                break;
            system->update(*this);
        }

        #ifdef DEBUG
            if (IsKeyPressed(KEY_F1)) {
                this->m_debug = !this->m_debug;

                if (this->m_debug) {
                    Scene &scene = this->getCurrentScene();
                    bool clickSystem = false;

                    for (auto &entity : scene.entities) {
                        if (scene != this->getCurrentScene())
                            break;
                        if (this->has<ecs::Clickable>(entity))
                            clickSystem = true;
                        this->addClickableComponent(&entity);
                    }

                    if (!clickSystem)
                        this->registerSystem<ClickableSystem>(scene);
                }
            }

            if (this->m_debug) {
                this->drawDebugTab();
                this->drawFps();
                this->drawEntityInfo();
            }
        #endif
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

    #ifdef DEBUG
        void SceneManager::drawFps() {
            std::string fps = "FPS: " + std::to_string(GetFPS());

            DrawText(fps.c_str(), 1920 - 280, 40, 20, ::WHITE);
        }

        void SceneManager::addClickableComponent(Entity *entity) {
            this->assign<ecs::Clickable>(*entity, ecs::Clickable{ false, [this](ecs::Clickable&, ecs::Entity *entity) {
                // if (this->m_clickedEntity != nullptr && this->m_clickedEntity != entity) {
                //     std::cout << "Old entity: " << this->m_clickedEntity->id << ", new entity: " << entity->id << std::endl;
                //     this->assign<ecs::Clickable>(*this->m_clickedEntity, this->m_clickedEntityClickable);
                // }

                // if (this->m_clickedEntity && this->m_clickedEntity == entity) {
                //     std::cout << "Do not display entity: " << entity->id << std::endl;
                //     this->assign<ecs::Clickable>(*this->m_clickedEntity, this->m_clickedEntityClickable);
                //     this->m_clickedEntity = nullptr;
                //     this->m_clickedEntityClickable = {};
                // } else {
                //     std::cout << "New entity: " << entity->id << std::endl;
                //     this->m_clickedEntity = entity;
                //     this->m_clickedEntityClickable = this->get<ecs::Clickable>(*entity);
                // }

                this->m_clickedEntity = entity;
            }});
        }

        void SceneManager::drawDebugTab() {
            DrawRectangle(1920 - 300, 0, 300, 1080, ::BLACK);
            DrawRectangleLines(1920 - 300, 0, 300, 1080, ::GRAY);
        }

        void SceneManager::drawEntityInfo() {
            if (this->m_clickedEntity != nullptr) {
                std::string info = "Entity id: " + std::to_string(this->m_clickedEntity->id) + "\n\n";

                for (auto &component : this->m_clickedEntity->components) {
                    info += "Component: " + std::string(component.first.name()) + "\n\n";
                }

                DrawText(info.c_str(), 1920 - 280, 40, 20, ::WHITE);
            }
        }
    #endif
}
