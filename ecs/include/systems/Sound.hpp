#ifndef SOUND_SYSTEM_HPP_
#define SOUND_SYSTEM_HPP_

#include <vector>
// #include "raylib.h"
#include "components/Sound.hpp"
#include "ISystem.hpp"

namespace ecs {

    /**
     * @class SoundSystem
     * @brief System for handling sound in the Entity Component System (ECS).
     * 
     * @details
     * The SoundSystem class is a specific system designed to manage and update sound-related components within the ECS framework.
     */
    class SoundSystem : public ISystem {
    public:
        /**
         * @brief Update method for the SoundSystem.
         * 
         * @details
         * This method is called to update the state of the SoundSystem. It should be implemented to handle sound-related logic.
         * 
         * @param sceneManager Reference to the SceneManager managing the current scene and its entities.
         */
        void update(SceneManager &sceneManager) override;
    };

} // namespace ecs

#endif /* !SOUND_SYSTEM_HPP_ */
