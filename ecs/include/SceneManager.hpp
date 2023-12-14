#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <vector>
#include <algorithm>
#include "raylib.h"
#include "Scene.hpp"
#include "systems/ISystem.hpp"
#include "Macros.hpp"

namespace ecs {
    class SceneManager {
        std::vector<Scene> m_scenes;
        std::size_t m_nextSceneId;
        std::size_t m_currentSceneId;
        std::size_t m_nextEntityId;
        std::unordered_map<std::string_view, Texture2D> m_textures;
        std::unordered_map<std::string_view, ::Music> m_musics;

        public:
            SceneManager() : m_scenes(), m_nextSceneId(0), m_currentSceneId(0), m_nextEntityId(0) {
                this->m_scenes.reserve(DEFAULT_NB_SCENES);
            }

            ~SceneManager() {
                this->m_scenes.clear();
            }

            Scene &createScene();
            void destroyScene(Scene &scene);

            void switchToScene(std::size_t sceneId);
            Scene &getCurrentScene();

            Entity &createEntity(Scene &scene);
            void destroyEntity(Scene &scene, Entity &entity);

            template<typename Component>
            void assign(Entity &entity, Component &component) {
                entity.components[typeid(Component).name()] = &component;
            }

            template<typename Component>
            void remove(Entity &entity) {
                entity.components.erase(typeid(Component).name());
            }

            template<typename Component>
            Component &get(Entity &entity) {
                return *static_cast<Component *>(entity.components[typeid(Component).name()]);
            }

            template<typename... Components>
            auto view(Scene &scene) {
                std::vector<Entity *> matchingEntities;

                for (auto &entity : scene.entities) {
                    if (hasComponents<Components...>(entity)) {
                        matchingEntities.push_back(&entity);
                    }
                }

                return matchingEntities;
            }

            template<typename... Systems>
            void registerSystems(Scene &scene) {
                (this->registerSystem<Systems>(scene), ...);
            }

            void update() {
                for (auto &system : this->m_scenes.at(this->m_currentSceneId).systems) {
                    system->update(*this);
                }
            }

            Texture2D &getTexture(std::string_view path);
            
            ::Music &getMusic(std::string_view path);

        private:
            template<typename... Components>
            bool hasComponents(Entity &entity) {
                return ((entity.components.find(typeid(Components).name()) != entity.components.end()) && ...);
            }

            template<typename System>
            void registerSystem(Scene &scene) {
                scene.systems.push_back(std::make_unique<System>());
            }
    };
}

#endif /* SCENE_MANAGER_HPP */
