#ifndef CONTROLABLE_SYSTEM_HPP
#define CONTROLABLE_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Acceleration.hpp"
#include "components/Controllable.hpp"
#include "components/Sound.hpp"
#include "ISystem.hpp"

namespace ecs {
    class SceneManager;

    /**
     * @class ControllableSystem
     * @brief Controllable System class
     * 
     * @details
     * Part of the Entity Component System, this class is responsible for handling user inputs and updating the state of controllable entities. It works in conjunction with Controllable, Acceleration, and Sound components to manage entity control and interaction.
     * 
     */
    class ControllableSystem : public ISystem {
    public:
        /**
         * @brief Updates the state of controllable entities based on user inputs
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;
    };
}

#endif /* CONTROLABLE_SYSTEM_HPP */
