#ifndef TEXT_SYSTEM_HPP
#define TEXT_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Position.hpp"
#include "components/Text.hpp"
#include "components/Color.hpp"
#include "components/FontSize.hpp"
#include "systems/ISystem.hpp"

namespace ecs {

    /**
     * @class TextSystem
     * @brief Text System class
     * 
     * @details
     * Part of the Entity Component System, this class is responsible for updating and rendering text associated with entities. It utilizes Text, Position, Color, and FontSize components to display text elements within the scene.
     * 
     */
    class TextSystem : public ISystem {
    public:
        /**
         * @brief Updates and renders the text of entities
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;
    };
}

#endif /* TEXT_SYSTEM_HPP */
