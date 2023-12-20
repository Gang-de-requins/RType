#ifndef CONTROLLABLE_COMPONENT_HPP
#define CONTROLLABLE_COMPONENT_HPP

    #include <chrono>

namespace ecs {
    struct Controllable {
        int keyUp;
        int keyDown;
        int keyLeft;
        int keyRight;
        int keySpace;
        float timeOut;
        std::chrono::steady_clock::time_point shootUpadte;
    };
}

#endif /* CONTROLLABLE_COMPONENT_HPP */
