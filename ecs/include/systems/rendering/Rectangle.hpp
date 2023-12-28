#ifndef RECTANGLE_SYSTEM_HPP
#define RECTANGLE_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Position.hpp"
#include "components/Rectangle.hpp"
#include "components/Scale.hpp"
#include "components/Rotation.hpp"
#include "systems/ISystem.hpp"

namespace ecs {

    /**
     * @class RectangleSystem
     * @brief Rectangle System class
     * 
     * @details
     * This class is a part of the Entity Component System and is responsible for updating and rendering rectangles of entities. It utilizes Position, Rectangle, Scale, and Rotation components to display rectangles within the scene.
     * 
     */
    class RectangleSystem : public ISystem {
    public:
        /**
         * @brief Updates and renders the rectangles of entities
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;
    };
}

#endif /* RECTANGLE_SYSTEM_HPP */
