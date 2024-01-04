#ifndef CONTROLLABLE_COMPONENT_HPP
#define CONTROLLABLE_COMPONENT_HPP

#include <chrono>

namespace ecs {

    /**
     * @struct Controllable
     * @brief Controllable component
     * 
     * @details
     * This component is used to add control functionality to an entity. It stores key bindings for different actions and control-related timings.
     * 
     * @var Controllable::keyUp
     * Key binding for moving the entity upwards.
     * 
     * @var Controllable::keyDown
     * Key binding for moving the entity downwards.
     * 
     * @var Controllable::keyLeft
     * Key binding for moving the entity to the left.
     * 
     * @var Controllable::keyRight
     * Key binding for moving the entity to the right.
     * 
     * @var Controllable::keySpace
     * Key binding for triggering a specific action, like shooting.
     * 
     * @var Controllable::timeOut
     * The time interval (in seconds) for certain actions, like the delay between shots.
     * 
     * @var Controllable::shootUpdate
     * A time point used to track the last update or action (e.g., last shot fired).
     */
    struct Controllable {
        int keyUp;
        int keyDown;
        int keyLeft;
        int keyRight;
        int keySpace;
        float timeOut;
        std::chrono::steady_clock::time_point shootUpdate;
    };
}

#endif /* CONTROLLABLE_COMPONENT_HPP */
