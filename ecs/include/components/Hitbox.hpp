#ifndef HITBOX_COMPONENT_HPP
#define HITBOX_COMPONENT_HPP

#include <string>
#include <vector>

namespace ecs {

    struct Hitbox {
        float w;
        float h;
        std::string tag;
        std::vector<std::string> collidesWith;
        bool hit;
    };
}

#endif /*HITBOX_COMPONENT_HPP*/
