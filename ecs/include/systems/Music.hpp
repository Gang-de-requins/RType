#ifndef MUSIC_SYSTEM_HPP
#define MUSIC_SYSTEM_HPP

#include <vector>
#include "raylib.h"
#include "components/Music.hpp"
#include "ISystem.hpp"

namespace ecs {

    /**
     * @class MusicSystem
     * @brief System responsible for handling music in the Entity Component System (ECS).
     * 
     * @details
     * The MusicSystem class is a specific system designed to manage and update music-related components within the ECS framework.
     */
    class MusicSystem : public ISystem {
    public:
        /**
         * @brief Update method for the MusicSystem.
         * 
         * @details
         * This method is called to update the state of the MusicSystem. It should be implemented to handle music-related logic.
         * 
         * @param sceneManager Reference to the SceneManager managing the current scene and its entities.
         */
        void update(SceneManager &sceneManager) override;
    };

} // namespace ecs

#endif /* MUSIC_SYSTEM_HPP */
