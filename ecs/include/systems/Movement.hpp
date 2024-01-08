#ifndef MOVEMENT_SYSTEM_HPP
#define MOVEMENT_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "components/Position.hpp"
#include "components/Velocity.hpp"
#include "components/Acceleration.hpp"
#include "../Entity.hpp"
#include "ISystem.hpp"

namespace ecs {
    class SceneManager;

    /**
     * @class MovementSystem
     * @brief Movement System class
     * 
     * @details
     * Part of the Entity Component System, the MovementSystem class is responsible for updating the position and movement of entities. It works with Position, Velocity, and Acceleration components to calculate and update entity movement based on physics and game logic.
     * 
     * Inherits from ISystem and overrides the update method to implement the movement logic for entities.
     */
    class MovementSystem : public ISystem {
        public:
            /**
             * @brief Updates the movement and position of entities
             * 
             * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
             * 
             * This method iterates through entities with Position, Velocity, and Acceleration components, updating their positions based on their velocities and accelerations. It handles the physics and movement logic for the entities.
             */
            void update(SceneManager &sceneManager) override;

        private:
            void move(SceneManager &sceneManager, Entity *entity);
    };
}

#endif /* MOVEMENT_SYSTEM_HPP */
