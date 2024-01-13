#ifndef NAME_SYSTEM_HPP
#define NAME_SYSTEM_HPP

#include <vector>
// #include "raylib.h"
#include <SFML/Graphics.hpp>
#include "components/Name.hpp"
#include "components/Position.hpp"
#include "systems/ISystem.hpp"

namespace ecs {

    /**
     * @class NameSystem
     * @brief Name System class
     * 
     * @details
     * This class is part of the Entity Component System and is responsible for updating and managing the names of entities. It works in conjunction with the Name and Position components to display or use the names of entities within the scene.
     * 
     */
    class NameSystem : public ISystem {
    public:
        /**
         * @brief Updates the name states of entities
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;
    };
}

#endif /* NAME_SYSTEM_HPP */
