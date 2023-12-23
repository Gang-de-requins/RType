#ifndef POSITION_COMPONENT_HPP
#define POSITION_COMPONENT_HPP

namespace ecs {

    /**
     * @struct Position
     * @brief Position component
     * 
     * @details
     * This component is used to store and manage the position of an entity in a 2D space. It holds coordinates in the x and y axes.
     * 
     * @var Position::x
     * The x-coordinate of the entity's position.
     * 
     * @var Position::y
     * The y-coordinate of the entity's position.
     */
    struct Position {
        float x;
        float y;
    };
}

#endif /* POSITION_COMPONENT_HPP */
