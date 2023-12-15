#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <memory>
#include <any>
#include <string_view>

namespace ecs {
    struct Entity {
        std::size_t id;
        std::unordered_map<std::string_view, std::any> components;
    };
}

#endif /* ENTITY_HPP */
