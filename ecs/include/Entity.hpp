#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <string_view>

namespace ecs {
    struct Entity {
        std::size_t id;
        std::unordered_map<std::string_view, void *> components;
    };
}

#endif /* ENTITY_HPP */
