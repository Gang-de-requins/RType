#ifndef SCENE_MANAGER_HPP
#define SCENE_MANAGER_HPP

#include <vector>
#include <algorithm>
#include "raylib.h"
#include "Scene.hpp"
#include "ParserJson.hpp"
#include "systems/ISystem.hpp"
#include "Macros.hpp"

namespace ecs {
    /**
     * @class SceneManager
     * @brief Scene manager
     * 
     * @details
     * This class is used to manage scenes.
     * 
     * @var SceneManager::m_scenes
     * The scenes.
     * 
     * @var SceneManager::m_nextSceneId
     * The id of the next scene.
     * 
     * @var SceneManager::m_currentSceneId
     * The id of the current scene.
     * 
     * @var SceneManager::m_nextEntityId
     * The id of the next entity.
     * 
     * @var SceneManager::m_textures
     * The textures.
     * 
     * @var SceneManager::m_musics
     * The musics.
     */
    class SceneManager {
        std::vector<Scene> m_scenes; // Scenes
        std::size_t m_nextSceneId; // Next scene id
        std::size_t m_currentSceneId; // Current scene id
        std::size_t m_nextEntityId; // Next entity id
        std::unordered_map<std::string, Texture2D> m_textures; // Textures
        std::unordered_map<std::string, ::Music> m_musics; // Musics
        std::unordered_map<std::string, ::Sound> m_sounds; // Sounds

        public:
            /**
             * @fn SceneManager::SceneManager
             * @brief Construct a new Scene Manager object
             * 
             */
            SceneManager() : m_scenes(), m_nextSceneId(0), m_currentSceneId(0), m_nextEntityId(0) {
                this->m_scenes.reserve(DEFAULT_NB_SCENES);
            }

            /**
             * @fn SceneManager::~SceneManager
             * @brief Destroy the Scene Manager object
             * 
             */
            ~SceneManager() {
                this->m_scenes.clear();
            }

            /**
             * @fn SceneManager::createScene
             * @brief Create a scene
             * 
             * @return The created scene.
             */
            Scene &createScene();
            /**
             * @fn SceneManager::destroyScene
             * @brief Destroy a scene
             * 
             * @param scene The scene to destroy.
             */
            void destroyScene(Scene &scene);

            /**
             * @fn SceneManager::unloadScene
             * @brief Unload a scene (remove all entities)
             * 
             * @param scene The scene to unload.
             */
            void unloadScene(Scene &scene);

            /**
             * @fn SceneManager::switchToScene
             * @brief Switch to a scene
             * 
             * @param sceneId The id of the scene to switch to.
             */
            void switchToScene(std::size_t sceneId);
            /**
             * @fn SceneManager::getCurrentScene
             * @brief Get the current scene
             * 
             * @return The current scene.
             */
            Scene &getCurrentScene();

            /**
             * @fn SceneManager::createEntity
             * @brief Create an entity
             * 
             * @param scene The scene in which the entity will be created.
             * @return The created entity.
             */
            Entity &createEntity(Scene &scene);
            /**
             * @fn SceneManager::destroyEntity
             * @brief Destroy an entity
             * 
             * @param scene The scene in which the entity will be destroyed.
             * @param entity The entity to destroy.
             */
            void destroyEntity(Scene &scene, Entity &entity);

            /**
             * @fn SceneManager::getEntityById
             * @brief Get an entity by its id
             * 
             * @param scene The scene in which the entity will be retrieved.
             * @param id The id of the entity.
             * @return The entity.
             */
            Entity &getEntityById(Scene &scene, std::size_t id);

            Scene &getSceneById(std::size_t id);
            /**
             * @fn SceneManager::assign
             * @brief Assign a component to an entity
             * 
             * @tparam Component The type of the component.
             * @param entity The entity to which the component will be assigned.
             * @param component The component to assign.
             */
            template<typename Component>
            void assign(Entity &entity, Component component) {
                entity.components[std::type_index(typeid(Component))] = std::make_any<Component>(component);
            }

            /**
             * @fn SceneManager::remove
             * @brief Remove a component from an entity
             * 
             * @tparam Component The type of the component.
             * @param entity The entity from which the component will be removed.
             */
            template<typename Component>
            void remove(Entity &entity) {
                entity.components.erase(std::type_index(typeid(Component)));
            }

            /**
             * @fn SceneManager::has
             * @brief Check if an entity has a component
             * 
             * @tparam Component The type of the component.
             * @param entity The entity to check.
             * @return true if the entity has the component, false otherwise.
             */
            template<typename Component>
            bool has(Entity &entity) {
                return entity.components.find(std::type_index(typeid(Component))) != entity.components.end();
            }

            /**
             * @fn SceneManager::get
             * @brief Get a component from an entity
             * 
             * @tparam Component The type of the component.
             * @param entity The entity from which the component will be retrieved.
             * @return The component.
             */
            template<typename Component>
            Component &get(Entity &entity) {
                try {
                    return std::any_cast<Component &>(entity.components.at(std::type_index(typeid(Component))));
                } catch (std::exception &e) {
                    std::cerr << e.what() << std::endl;
                    throw;
                }
            }

            /**
             * @fn SceneManager::view
             * @brief Get the entities matching the given components
             * 
             * @tparam Components The types of the components.
             * @param scene The scene in which the entities will be retrieved.
             * @return The entities matching the given components.
             */
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

            /**
             * @fn SceneManager::registerSystems
             * @brief Register systems
             * 
             * @tparam Systems The types of the systems.
             * @param scene The scene in which the systems will be registered.
             */
            template<typename... Systems>
            void registerSystems(Scene &scene) {
                (this->registerSystem<Systems>(scene), ...);
            }

            /**
             * @fn SceneManager::update
             * @brief Update the scene
             * 
             */
            void update();

            /**
             * @fn SceneManager::loadTextures
             * @brief Load textures
             * 
             * @param path The path to the textures.
             */
            void loadTextures(std::vector<std::string> &paths);

            /**
             * @fn SceneManager::loadMusics
             * @brief Load musics
             * 
             * @param paths The paths to the musics.
             */
            void loadMusics(std::vector<std::string> &paths);

            /**
             * @fn SceneManager::loadSounds
             * @brief Load sounds
             * 
             * @param paths The paths to the sounds.
             */
            void loadSounds(std::vector<std::string> &paths);

            /**
             * @fn SceneManager::getTexture
             * @brief Get a texture
             * 
             * @param path The path to the texture.
             * @return The texture.
             */
            Texture2D &getTexture(std::string path);

            /**
             * @fn SceneManager::getMusic
             * @brief Get a music
             * 
             * @param paths The path to the music.
             * @return The music.
             */
            ::Music &getMusic(std::string path);

            /**
             * @fn SceneManager::getSound
             * @brief Get a sound
             * 
             * @param path The path to the sound.
             * @return The sound.
             */
            ::Sound &getSound(std::string path);

        private:
            /**
             * @fn SceneManager::hasComponents
             * @brief Check if an entity has the given components
             * 
             * @tparam Components The types of the components.
             * @param entity The entity to check.
             * @return true if the entity has the given components, false otherwise.
             */
            template<typename... Components>
            bool hasComponents(Entity &entity) {
                return ((entity.components.find(std::type_index(typeid(Components))) != entity.components.end()) && ...);
            }

            /**
             * @fn SceneManager::registerSystem
             * @brief Register a system
             * 
             * @tparam System The type of the system.
             * @param scene The scene in which the system will be registered.
             */
            template<typename System>
            void registerSystem(Scene &scene) {
                scene.systems.push_back(std::make_unique<System>());
            }

            /**
             * @fn SceneManager::loadEntitiesFromJson
             * @brief Load entities from a json file
             * 
             * @param scene The scene in which the entities will be loaded.
             */
            void loadEntitiesFromJson(Scene &scene);
    };
}

#endif /* SCENE_MANAGER_HPP */
