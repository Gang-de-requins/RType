#ifndef CLICKABLE_COMPONENT_HPP_
#define CLICKABLE_COMPONENT_HPP_

#include <functional>

namespace ecs {

    /**
     * @struct Clickable
     * @brief Clickable component
     * 
     * @details
     * This component is used to make an entity interactive, such as making it respond to mouse clicks.
     * 
     * @var Clickable::clickable
     * A boolean value indicating whether the entity is clickable or not.
     * 
     * @var Clickable::onClick
     * A std::function that defines the action to be performed when the entity is clicked. It takes a reference to Clickable as an argument.
     */
    struct Clickable {
        bool clickable;
        std::function<void(Clickable&)> onClick;
}

#endif /* CLICKABLE_COMPONENT_HPP_ */
