#ifndef ENTITY_HPP
#define ENTITY_HPP

#include <unordered_map>
#include <memory>
#include <any>
#include <string_view>

namespace ecs {
    /**
     * @struct Entity
     * @brief Entity
     * 
     * @details
     * This struct is used to store an entity.
     * 
     * @var Entity::id
     * The id of the entity.
     * 
     * @var Entity::components
     * The components of the entity.
     */
    struct Entity {
        std::size_t id;
        std::unordered_map<std::string_view, std::any> components;
    };
}

#endif /* ENTITY_HPP */
