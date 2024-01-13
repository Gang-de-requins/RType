#ifndef CONTROLLABLE_COMPONENT_HPP
#define CONTROLLABLE_COMPONENT_HPP

#include <unordered_map>
#include <functional>
#include <tuple>
#include "Scene.hpp"
#include "Entity.hpp"

namespace ecs {
    class SceneManager;

    enum ActionTrigger {
        Press,
        Release,
        Hold,
        MouseLeftClick,
        MouseRightClick,
        MouseLeftRelease,
        MouseRightRelease,
        MouseLeftHold,
        MouseRightHold,
        MouseLeftDoubleClick,
        MouseRightDoubleClick
    };

    struct Controllable {
        std::unordered_map<int, std::tuple<ActionTrigger, std::function<void(SceneManager &sceneManager, Scene &scene, Entity *entity)>>> actions;
    };
}

#endif /* CONTROLLABLE_COMPONENT_HPP */
