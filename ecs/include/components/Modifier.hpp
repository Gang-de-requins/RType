#ifndef MODIFIER_COMPONENT_HPP
#define MODIFIER_COMPONENT_HPP

#include <unordered_map>
#include <typeindex>
#include <any>
#include <thread>
#include <mutex>

namespace ecs {
    struct Modifier {
        std::unordered_map<std::type_index, std::any> modifiers;
        bool isPermanent;
        float duration = 0.0f; // in milliseconds
    };
}

#endif /* MODIFIER_COMPONENT_HPP */
