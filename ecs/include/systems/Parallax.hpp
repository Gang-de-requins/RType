/*
** EPITECH PROJECT, 2023
** RType
** File description:
** Parallax
*/

#ifndef PARALLAX_SYSTEM_HPP_
#define PARALLAX_SYSTEM_HPP_

#include "ISystem.hpp"
#include "components/Parallax.hpp"
#include "components/Position.hpp"

namespace ecs {

    /**
     * @class ParallaxSystem
     * @brief System for handling parallax effects in the Entity Component System (ECS).
     * 
     * @details
     * The ParallaxSystem class is a specific system designed to manage and update parallax-related components within the ECS framework.
     */
    class ParallaxSystem : public ISystem {
    public:
        /**
         * @brief Update method for the ParallaxSystem.
         * 
         * @details
         * This method is called to update the state of the ParallaxSystem. It should be implemented to handle parallax-related logic.
         * 
         * @param sceneManager Reference to the SceneManager managing the current scene and its entities.
         */
        void update(SceneManager &sceneManager) override;
    };

}

#endif /* !PARALLAX_SYSTEM_HPP_ */
