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
    class World {
        EntityID _nextEntity;
        ComponentTypeID _nextComponentType;
        std::unordered_map<EntityID, ArchetypeID> _entityToArchetypeMap;
        std::unordered_map<ArchetypeID, std::shared_ptr<Archetype>> _archetypes;
        std::unordered_map<const char*, ComponentTypeID> _componentTypes;
        std::unordered_map<const char*, ArchetypeID> _systemToArchetypeMap;
        std::unordered_map<const char*, std::shared_ptr<System>> _systems;

        private:
            void addComponentType(const char *&typeName) noexcept;
            ArchetypeID updateEntityArchetypeID(const EntityID &entity, const ComponentTypeID &componentType, const bool &isSet);
            void createArchetype(const ArchetypeID &archetypeId) noexcept;
            void updateSystemArchetype(const char *&systemTypeName, ArchetypeID &systemArchetypeId) noexcept;

            template<typename C>
            void addComponentToEntityArchetype(const EntityID &entity, C &component, const ComponentTypeID &componentType) noexcept
            {
                ArchetypeID oldArchetypeId = this->_entityToArchetypeMap.at(entity);
                ArchetypeID newArchetypeId = this->updateEntityArchetypeID(entity, componentType, true);

                if (this->_archetypes.find(newArchetypeId) == this->_archetypes.end()) {
                    this->createArchetype(newArchetypeId);
                }

                std::shared_ptr<Archetype> newArchetype = this->_archetypes.at(newArchetypeId);
                newArchetype->addEntity(entity);

                if (oldArchetypeId.any()) {
                    std::shared_ptr<Archetype> oldArchetype = this->_archetypes.at(oldArchetypeId);
                    oldArchetype->removeEntity(entity);
                    oldArchetype->transferComponents(entity, newArchetype);
                }

                newArchetype->addComponent(entity, component);
            }

            template<typename C>
            void updateComponentEntityArchetype(const EntityID &entity, C &component) noexcept
            {
                ArchetypeID archetypeId = this->_entityToArchetypeMap.at(entity);

                if (this->_archetypes.find(archetypeId) == this->_archetypes.end()) {
                    std::cerr << "Archetype does not exist." << std::endl;
                    return;
                }

                std::shared_ptr<Archetype> archetype = this->_archetypes.at(archetypeId);

                archetype->updateComponent(entity, component);
            }

        public:
            World() noexcept;
            EntityID createEntity() noexcept;
            void destroyEntity(const EntityID &entity) noexcept;

            template<typename C>
            void addComponentToEntity(EntityID entity, C component) noexcept
            {
                const char *typeName = typeid(C).name();

                if (this->_componentTypes.find(typeName) == this->_componentTypes.end()) {
                    this->addComponentType(typeName);
                }

                ComponentTypeID componentTypeId = this->_componentTypes.at(typeName);

                this->addComponentToEntityArchetype(entity, component, componentTypeId);
            }

            template<typename C>
            void updateComponentToEntity(EntityID entity, C component) noexcept
            {
                const char *typeName = typeid(C).name();

                if (this->_componentTypes.find(typeName) == this->_componentTypes.end()) {
                    std::cerr << "Component type not registered." << std::endl;
                    return;
                }

                this->updateComponentEntityArchetype(entity, component);
            }

            template<typename S>
            std::shared_ptr<S> addSystem() noexcept
            {
                const char *typeName = typeid(S).name();

                if (this->_systems.find(typeName) != this->_systems.end()) {
                    std::cerr << "Added system more than once." << std::endl;
                    return nullptr;
                }

                std::shared_ptr<S> system = std::make_shared<S>();

                this->_systems.insert({typeName, system});

                this->_systemToArchetypeMap.insert({typeName, ArchetypeID()});

                return system;
            }

            template<typename S, typename C>
            void addComponentToSystem() noexcept
            {
                const char *systemTypeName = typeid(S).name();
                const char *componentTypeName = typeid(C).name();

                if (this->_systems.find(systemTypeName) == this->_systems.end()) {
                    std::cerr << "System not registered." << std::endl;
                    return;
                }
                
                if (this->_componentTypes.find(componentTypeName) == this->_componentTypes.end()) {
                    this->addComponentType(componentTypeName);
                }

                ComponentTypeID componentTypeId = this->_componentTypes.at(componentTypeName);
                ArchetypeID systemArchetypeId = this->_systemToArchetypeMap.at(systemTypeName).set(componentTypeId, true);

                this->updateSystemArchetype(systemTypeName, systemArchetypeId);
            }

            template<typename S, typename C>
            void removeComponentFromSystem() noexcept
            {
                const char *systemTypeName = typeid(S).name();
                const char *componentTypeName = typeid(C).name();

                if (this->_systems.find(systemTypeName) == this->_systems.end()) {
                    std::cerr << "System not registered." << std::endl;
                    return;
                }
                
                if (this->_componentTypes.find(componentTypeName) == this->_componentTypes.end()) {
                    std::cerr << "Component type not registered." << std::endl;
                    return;
                }

                ComponentTypeID componentTypeId = this->_componentTypes.at(componentTypeName);
                ArchetypeID systemArchetypeId = this->_systemToArchetypeMap.at(systemTypeName).set(componentTypeId, false);

                this->updateSystemArchetype(systemTypeName, systemArchetypeId);
            }

            template<typename S>
            void removeSystem() noexcept
            {
                const char *typeName = typeid(S).name();

                if (this->_systems.find(typeName) == this->_systems.end()) {
                    std::cerr << "System not registered." << std::endl;
                    return;
                }

                this->_systems.erase(typeName);
                this->_systemToArchetypeMap.erase(typeName);
            }

            template<typename S>
            std::shared_ptr<S> getSystem() noexcept
            {
                const char *typeName = typeid(S).name();

                if (this->_systems.find(typeName) == this->_systems.end()) {
                    std::cerr << "System not registered." << std::endl;
                    return nullptr;
                }

                return std::dynamic_pointer_cast<S>(this->_systems.at(typeName));
            }

            template<typename C>
            C getComponentFromEntity(const EntityID &entity) noexcept
            {
                const char *typeName = typeid(C).name();

                if (this->_componentTypes.find(typeName) == this->_componentTypes.end()) {
                    std::cerr << "Component type not registered." << std::endl;
                    return C();
                }

                ArchetypeID archetypeId = this->_entityToArchetypeMap.at(entity);

                if (this->_archetypes.find(archetypeId) == this->_archetypes.end()) {
                    std::cerr << "Archetype does not exist." << std::endl;
                    return C();
                }

                std::shared_ptr<Archetype> archetype = this->_archetypes.at(archetypeId);

                return archetype->getComponent<C>(entity);
            }
    };
}

#endif /* WORLD_HPP */
