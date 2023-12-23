#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

namespace ecs {
    class SceneManager;

    /**
     * @class ISystem
     * @brief Interface for System classes
     * 
     * @details
     * This is an interface class for all system classes in the Entity Component System (ECS). It defines a common interface that all systems must implement, primarily the update method.
     * 
     */
    class ISystem {
    public:
        /**
         * @brief Virtual destructor
         * 
         * Ensures proper cleanup of derived system objects when deleted through a pointer to ISystem.
         */
        virtual ~ISystem() = default;

        /**
         * @brief Update method to be implemented by derived systems
         * 
         * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
         * 
         */
        virtual void update(SceneManager &sceneManager) = 0;
    };
}

#endif /* ISYSTEM_HPP */
