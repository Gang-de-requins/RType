#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <string_view>
#include "Entity.hpp"
#include "Events.hpp"

namespace ecs {
    class ISystem;

    /**
     * @struct Scene
     * @brief Scene
     * 
     * @details
     * This struct is used to store a scene.
     * 
     * @var Scene::id
     * The id of the scene.
     * 
     * @var Scene::entities
     * The entities of the scene.
     * 
     * @var Scene::systems
     * The systems of the scene.
     * 
     * @var Scene::path
     * The path of the scene.
     * 
     * @var Scene::loadFromPath
     * A boolean to know if the scene has to be loaded from its path.
     */
    struct Scene {
        std::size_t id;
        std::vector<Entity> entities;
        std::vector<std::unique_ptr<ISystem>> systems;
        std::unordered_map<EventType, std::vector<EventData>> events;
        std::string_view path;
        bool loadFromPath;

        bool operator==(const Scene &other) const {
            return this->id == other.id;
        }

        bool operator!=(const Scene &other) const {
            return this->id != other.id;
        }
    };
}

#endif /* SCENE_HPP */
