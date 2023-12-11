#ifndef WORLD_HPP
#define WORLD_HPP

#include <iostream>
#include <string_view>
#include <vector>
#include <memory>
#include <unordered_map>
#include "CustomExceptions.hpp"
#include "Archetype.hpp"
#include "System.hpp"
#include "Macros.hpp"

namespace ecs {
    /**
     * @brief Class representing the ECS (Entity Component System) world.
     */
    class World {
        EntityID _nextEntity; ///< The ID to assign to the next created entity.
        ComponentTypeID _nextComponentType; ///< The ID to assign to the next registered component type.
        std::unordered_map<EntityID, ArchetypeID> _entityToArchetypeMap; ///< Map to track the archetype of each entity.
        std::unordered_map<ArchetypeID, std::shared_ptr<Archetype>> _archetypes; ///< Map of archetypes in the world.
        std::unordered_map<const char*, ComponentTypeID> _componentTypes; ///< Map of registered component types.
        std::unordered_map<const char*, ArchetypeID> _systemToArchetypeMap; ///< Map to track the archetype associated with each system.
        std::unordered_map<const char*, std::shared_ptr<System>> _systems; ///< Map of registered systems.

    private:
        /**
         * @brief Adds a new component type to the world.
         * @param typeName The name of the component type.
         */
        void addComponentType(const char *&typeName) noexcept;

        /**
         * @brief Updates the archetype ID of an entity based on a component type.
         * @param entity The ID of the entity.
         * @param componentType The ID of the component type.
         * @param isSet Indicates whether the component type is being set or unset.
         * @return The updated archetype ID.
         */
        ArchetypeID updateEntityArchetypeID(const EntityID &entity, const ComponentTypeID &componentType, const bool &isSet);

        /**
         * @brief Creates a new archetype with the given ID.
         * @param archetypeId The ID of the archetype to be created.
         */
        void createArchetype(const ArchetypeID &archetypeId) noexcept;

        /**
         * @brief Updates the archetype associated with a system.
         * @param systemTypeName The name of the system type.
         * @param systemArchetypeId The ID of the archetype associated with the system.
         */
        void updateSystemArchetype(const char *&systemTypeName, ArchetypeID &systemArchetypeId) noexcept;

        /**
         * @brief Adds a component to the archetype of the entity.
         * @param entity The ID of the entity.
         * @param component The component to be added.
         * @param componentType The ID of the component type.
         */
        template<typename C>
        void addComponentToEntityArchetype(const EntityID &entity, C &component, const ComponentTypeID &componentType) noexcept;

        /**
         * @brief Updates a component in the archetype of the entity.
         * @param entity The ID of the entity.
         * @param component The component to be updated.
         */
        template<typename C>
        void updateComponentEntityArchetype(const EntityID &entity, C &component) noexcept;

    public:
        /**
         * @brief Default constructor for the World class.
         */
        World() noexcept;

        /**
         * @brief Creates a new entity and returns its ID.
         * @return The ID of the created entity.
         */
        EntityID createEntity() noexcept;

        /**
         * @brief Destroys the entity with the given ID.
         * @param entity The ID of the entity to be destroyed.
         */
        void destroyEntity(const EntityID &entity) noexcept;

        /**
         * @brief Adds a component to the entity.
         * @tparam C The type of the component to be added.
         * @param entity The ID of the entity.
         * @param component The component to be added.
         */
        template<typename C>
        void addComponentToEntity(EntityID entity, C component) noexcept;

        /**
         * @brief Updates a component in the entity's archetype.
         * @tparam C The type of the component to be updated.
         * @param entity The ID of the entity.
         * @param component The updated component.
         */
        template<typename C>
        void updateComponentToEntity(EntityID entity, C component) noexcept;

        /**
         * @brief Adds a system of type S to the world and returns a shared pointer to it.
         * @tparam S The type of the system to be added.
         * @return A shared pointer to the added system.
         */
        template<typename S>
        std::shared_ptr<S> addSystem() noexcept;

        /**
         * @brief Adds a component type to a system.
         * @tparam S The type of the system.
         * @tparam C The type of the component to be added to the system.
         */
        template<typename S, typename C>
        void addComponentToSystem() noexcept;

        /**
         * @brief Removes a component type from a system.
         * @tparam S The type of the system.
         * @tparam C The type of the component to be removed from the system.
         */
        template<typename S, typename C>
        void removeComponentFromSystem() noexcept;

        /**
         * @brief Removes a system of type S from the world.
         * @tparam S The type of the system to be removed.
         */
        template<typename S>
        void removeSystem() noexcept;

        /**
         * @brief Gets a shared pointer to a system of type S.
         * @tparam S The type of the system.
         * @return A shared pointer to the requested system.
         */
        template<typename S>
        std::shared_ptr<S> getSystem() noexcept;

        /**
         * @brief Gets the component of type C from the entity with the given ID.
         * @tparam C The type of the component to be retrieved.
         * @param entity The ID of the entity.
         * @return The retrieved component.
         */
        template<typename C>
        C getComponentFromEntity(const EntityID &entity) noexcept;
    };
}

#endif /* WORLD_HPP */
