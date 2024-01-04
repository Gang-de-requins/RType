#ifndef LIFE_SYSTEM_HPP
#define LIFE_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "components/Health.hpp"
#include "components/Damage.hpp"
#include "components/Collision.hpp"
#include "ISystem.hpp"

namespace ecs {
    class SceneManager;

    /**
     * @class LifeSystem
     * @brief Life System class
     * 
     * @details
     * Part of the Entity Component System, the LifeSystem class is responsible for managing the health and damage aspects of entities. It works with Health, Damage, and Collision components to handle health reduction, entity damage, and possibly death or destruction of entities.
     * 
     */
    class LifeSystem : public ISystem {
    public:
        /**
         * @brief Updates the life state of entities
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;
    };
}

#endif /* LIFE_SYSTEM_HPP */
