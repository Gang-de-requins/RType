#ifndef TEXTINPUT_SYSTEM_HPP
#define TEXTINPUT_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Position.hpp"
#include "components/Rectangle.hpp"
#include "components/Scale.hpp"
#include "components/Rotation.hpp"
#include "components/Text.hpp"
#include "components/TextInput.hpp"
#include "systems/ISystem.hpp"

namespace ecs {

    /**
     * @class TextInputSystem
     * @brief TextInput System class
     * 
     * @details
     * This class is a part of the Entity Component System and is responsible for updating and rendering text inputs of entities. It utilizes Position, Rectangle, Scale, and Rotation components to display text inputs within the scene.
     * 
     */
    class TextInputSystem : public ISystem {
    public:
        /**
         * @brief Updates and renders the text inputs of entities
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        void update(SceneManager &sceneManager) override;
    };
}

#endif /* TEXTINPUT_SYSTEM_HPP */
