#ifndef NAME_COMPONENT_HPP
#define NAME_COMPONENT_HPP

#include <string>
#include "Position.hpp"

namespace ecs {
    struct Name {
        std::string name;
        Position position;
    };
}

#endif /* NAME_COMPONENT_HPP */
