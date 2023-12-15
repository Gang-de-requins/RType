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
        SceneManager m_sceneManager;

        public:
            World() : m_sceneManager() {
            }

            ~World() {
            }
            Scene &createScene();
            void destroyScene(Scene &scene);

            void switchToScene(std::size_t sceneId);
            Scene &getCurrentScene();

            Entity &createEntity(Scene &scene);
            void destroyEntity(Scene &scene, Entity &entity);

            template<typename Component>
            void assign(Entity &entity, Component component) {
                entity.components[typeid(Component).name()] = std::make_any<Component>(component);
            }

            template<typename Component>
            void remove(Entity &entity) {
                entity.components.erase(typeid(Component).name());
            }

            template<typename Component>
            Component &get(Entity &entity) {
                try {
                    return std::any_cast<Component &>(entity.components.at(typeid(Component).name()));
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                    throw;
                }
            }

            template<typename... Systems>
            void registerSystems(Scene &scene) {
                this->m_sceneManager.registerSystems<Systems...>(scene);
            }

            void update();

            void loadTextures(std::vector<std::string> paths);

            void loadTexture(std::string path);
    };
}

#endif /* WORLD_HPP */
