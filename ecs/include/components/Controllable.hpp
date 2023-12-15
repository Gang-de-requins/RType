#ifndef CONTROLLABLE_COMPONENT_HPP
#define CONTROLLABLE_COMPONENT_HPP

namespace ecs {
    struct Controllable {
        int keyUp;
        int keyDown;
        int keyLeft;
        int keyRight;
    };
}

#endif /* CONTROLLABLE_COMPONENT_HPP */
