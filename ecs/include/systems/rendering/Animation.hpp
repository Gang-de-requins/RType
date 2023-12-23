#ifndef ANIMATION_SYSTEM_HPP
#define ANIMATION_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Animation.hpp"
#include "components/Sprite.hpp"
#include "systems/ISystem.hpp"

namespace ecs {

    /**
     * @class AnimationSystem
     * @brief Animation System class
     * 
     * @details
     * This class is part of the Entity Component System and is responsible for updating animations of entities. It works in conjunction with the Animation and Sprite components to animate entities within the scene.
     * 
     */
    class AnimationSystem : public ISystem {
    public:
        /**
         * @brief Updates the animation states of entities
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;
    };
}

#endif /* ANIMATION_SYSTEM_HPP */
