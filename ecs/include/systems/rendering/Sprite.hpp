#ifndef SPRITE_SYSTEM_HPP
#define SPRITE_SYSTEM_HPP

#include <vector>
// #include "raylib.h"
#include <SFML/Graphics.hpp>
#include "components/Position.hpp"
#include "components/Sprite.hpp"
#include "components/Scale.hpp"
#include "components/Rotation.hpp"
#include "systems/ISystem.hpp"

namespace ecs {

    /**
     * @class SpriteSystem
     * @brief Sprite System class
     * 
     * @details
     * This class is a part of the Entity Component System and is responsible for updating and rendering sprites of entities. It utilizes Position, Sprite, Scale, and Rotation components to display sprites within the scene.
     * 
     */
    class SpriteSystem : public ISystem {
    public:
        /**
         * @brief Updates and renders the sprites of entities
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;
    };
}

#endif /* SPRITE_SYSTEM_HPP */
