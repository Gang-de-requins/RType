#ifndef SCENE_HPP
#define SCENE_HPP

#include <vector>
#include <memory>
#include <string_view>
#include "Entity.hpp"

namespace ecs {
    class ISystem;

    struct Scene {
        std::size_t id;
        std::vector<Entity> entities;
        std::vector<std::unique_ptr<ISystem>> systems;
        std::string_view path;
        bool loadFromPath;
    };
}

#endif /* SCENE_HPP */
