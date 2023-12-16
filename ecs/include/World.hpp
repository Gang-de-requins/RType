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

/**
 * @namespace ecs
 * @brief Namespace of the ECS library
 * 
 * @details
 * This namespace contains all the classes and functions of the ECS library.
 */
namespace ecs {
    /**
     * @class World
     * @brief World class
     * 
     * @details
     * This class is used to manage the scenes and the entities.
     * 
     * @var World::m_sceneManager
     * The scene manager.
     * 
     */
    class World {
        SceneManager m_sceneManager; // Scene manager

        public:
            /**
             * @fn World::World
             * @brief Construct a new World object
             * 
             */
            World() : m_sceneManager() {
            }

            /**
             * @fn World::~World
             * @brief Destroy the World object
             * 
             */
            ~World() {
            }
            /**
             * @fn World::createScene
             * @brief Create a scene
             * 
             * @return The created scene.
             */
            Scene &createScene();
            /**
             * @fn World::destroyScene
             * @brief Destroy a scene
             * 
             * @param scene The scene to destroy.
             */
            void destroyScene(Scene &scene);

            /**
             * @fn World::switchToScene
             * @brief Switch to a scene
             * 
             * @param sceneId The id of the scene to switch to.
             */
            void switchToScene(std::size_t sceneId);
            /**
             * @fn World::getCurrentScene
             * @brief Get the current scene
             * 
             * @return The current scene.
             */
            Scene &getCurrentScene();

            /**
             * @fn World::createEntity
             * @brief Create an entity
             * 
             * @param scene The scene in which the entity will be created.
             * @return The created entity.
             */
            Entity &createEntity(Scene &scene);
            /**
             * @fn World::destroyEntity
             * @brief Destroy an entity
             * 
             * @param scene The scene in which the entity will be destroyed.
             * @param entity The entity to destroy.
             */
            void destroyEntity(Scene &scene, Entity &entity);

            /**
             * @fn World::assign
             * @brief Assign a component to an entity
             * 
             * @tparam Component The type of the component to assign.
             * @param entity The entity to which the component will be assigned.
             * @param component The component to assign.
             */
            template<typename Component>
            void assign(Entity &entity, Component component) {
                entity.components[typeid(Component).name()] = std::make_any<Component>(component);
            }

            /**
             * @fn World::remove
             * @brief Remove a component from an entity
             * 
             * @tparam Component The type of the component to remove.
             * @param entity The entity from which the component will be removed.
             */
            template<typename Component>
            void remove(Entity &entity) {
                entity.components.erase(typeid(Component).name());
            }

            /**
             * @fn World::get
             * @brief Get a component from an entity
             * 
             * @tparam Component The type of the component to get.
             * @param entity The entity from which the component will be get.
             * @return The component.
             */
            template<typename Component>
            Component &get(Entity &entity) {
                try {
                    return std::any_cast<Component &>(entity.components.at(typeid(Component).name()));
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                    throw;
                }
            }

            /**
             * @fn World::registerSystems
             * @brief Register systems
             * 
             * @tparam Systems The systems to register.
             * @param scene The scene in which the systems will be registered.
             */
            template<typename... Systems>
            void registerSystems(Scene &scene) {
                this->m_sceneManager.registerSystems<Systems...>(scene);
            }

            /**
             * @fn World::update
             * @brief Update the world
             * 
             */
            void update();

            /**
             * @fn World::loadTextures
             * @brief Load textures
             * 
             * @param paths The paths of the textures to load.
             */
            void loadTextures(std::vector<std::string> paths);

            /**
             * @fn World::loadTexture
             * @brief Load a texture
             * 
             * @param path The path of the texture to load.
             */
            void loadTexture(std::string path);
    };
}

#endif /* WORLD_HPP */
