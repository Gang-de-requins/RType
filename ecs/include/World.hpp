#ifndef WORLD_HPP
#define WORLD_HPP

#include <unordered_map>
#include <string_view>
#include <vector>
#include <algorithm>
#include <typeinfo>
#include "Entity.hpp"
#include "SceneManager.hpp"
#include "Macros.hpp"

namespace ecs {
    class World {
        // std::vector<Entity> m_entities;
        // std::size_t m_nextEntityId;
        // std::unordered_map<std::string_view, Texture2D> m_textures;
        // std::unordered_map<std::string_view, ::Music> m_musics;
        SceneManager m_sceneManager;

        public:
            World() : m_sceneManager() {
                // this->m_entities.reserve(DEFAULT_NB_ENTITIES);
            }

            ~World() {
                // this->m_entities.clear();
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

            template<typename... Systems>
            void registerSystems(Scene &scene) {
                this->m_sceneManager.registerSystems<Systems...>(scene);
            }

            void update() {
                this->m_sceneManager.update();
            }

            // template<typename Component>
            // Component &get(Entity &entity) {
            //     return *static_cast<Component *>(entity.components[typeid(Component).name()]);
            // }

            // template<typename... Components>
            // auto view() {
            //     std::vector<Entity *> matchingEntities;

            //     for (auto &entity : this->m_entities) {
            //         if (hasComponents<Components...>(entity)) {
            //             matchingEntities.push_back(&entity);
            //         }
            //     }

            //     return matchingEntities;
            // }

            // Texture2D &getTexture(std::string_view path);

            // ::Music &getMusic(std::string_view path);

        // private:
        //     template<typename... Components>
        //     bool hasComponents(Entity &entity) {
        //         return ((entity.components.find(typeid(Components).name()) != entity.components.end()) && ...);
        //     }
    };
}

#endif /* WORLD_HPP */
