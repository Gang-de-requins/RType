#ifndef CLICKABLE_SYSTEM_HPP_
#define CLICKABLE_SYSTEM_HPP_

#include <vector>
#include <algorithm>
// #include "raylib.h"
#include <SFML/Graphics.hpp>
#include "components/Clickable.hpp"
#include "ISystem.hpp"
#include "Entity.hpp"

namespace ecs {

    /**
     * @class ClickableSystem
     * @brief Clickable System class
     * 
     * @details
     * This class is part of the Entity Component System and is responsible for handling click interactions for entities. It works with the Clickable component to detect and respond to mouse clicks on entities.
     * 
     * Inherits from ISystem and overrides the update method to provide clickable functionality.
     */
    class ClickableSystem : public ISystem {
    public:
        /**
         * @brief Updates the state of clickable entities
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;

    private:
        /**
         * @brief Determines if the mouse is over a sprite
         * 
         * @param mousePosition The current position of the mouse.
         * @param entitie The entity being checked for mouse hover.
         * @param sceneManager Reference to the SceneManager for accessing entity components.
         * 
         * @return bool True if the mouse is over the sprite of the entity, false otherwise.
         * 
         */
        bool mouseInSprite(sf::Vector2f mousePosition, Entity &entitie, SceneManager &sceneManager);
    };
}

#endif /* CLICKABLE_SYSTEM_HPP_ */
