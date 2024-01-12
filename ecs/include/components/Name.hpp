#ifndef NAME_COMPONENT_HPP
#define NAME_COMPONENT_HPP

#include <string>
#include "Position.hpp"

namespace ecs {

    /**
     * @struct Name
     * @brief Name component
     * 
     * @details
     * This component is used to store a name identifier and its associated position for an entity. It can be used for labeling or identification purposes in the game or application.
     * 
     * @var Name::name
     * The name identifier for the entity. This string can be used to label or uniquely identify the entity.
     * 
     * @var Name::position
     * The position where the name should be displayed or associated with, typically relative to the entity's own position.
     */
    struct Name {
        std::string name;
        Position position;
    };
}

#endif /* NAME_COMPONENT_HPP */

