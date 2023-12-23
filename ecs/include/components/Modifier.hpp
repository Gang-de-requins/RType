#ifndef MODIFIER_COMPONENT_HPP
#define MODIFIER_COMPONENT_HPP

#include <unordered_map>
#include <typeindex>
#include <any>
#include <thread>
#include <chrono>

namespace ecs {

    /**
     * @struct Modifier
     * @brief Modifier component
     * 
     * @details
     * This component is used to apply various modifiers to an entity. Modifiers are stored in a map, allowing for a flexible and dynamic system of attribute modifications. The component can handle both permanent and temporary modifiers.
     * 
     * @var Modifier::modifiers
     * An unordered map storing modifiers with a type index as the key and a generic 'any' type as the value. This allows for storing various types of modifiers.
     * 
     * @var Modifier::isPermanent
     * A boolean indicating whether the modifiers are permanent. If true, modifiers persist indefinitely; otherwise, they have a limited duration.
     * 
     * @var Modifier::duration
     * The duration for which the modifier is active, in milliseconds. This is relevant for non-permanent modifiers.
     */
    struct Modifier {
        std::unordered_map<std::type_index, std::any> modifiers;
        bool isPermanent;
        int duration;
    };
}

#endif /* MODIFIER_COMPONENT_HPP */
