#include "World.hpp"

namespace ecs {
    World::World() noexcept :
    _nextEntity { 0 },
    _nextComponentType { 0 },
    _entityToArchetypeMap { },
    _archetypes { }
    {
        std::cout << "New world created.\n";
    }

    EntityID World::createEntity() noexcept
    {
        EntityID newEntity = this->_nextEntity;

        this->_entityToArchetypeMap.insert({ newEntity, ArchetypeID() });
        this->_nextEntity++;
        return newEntity;
    }

    void World::destroyEntity(const EntityID &entity) noexcept
    {
        if (this->_entityToArchetypeMap.at(entity).any()) {
            std::shared_ptr<Archetype> archetype = this->_archetypes.at(this->_entityToArchetypeMap.at(entity));
            archetype->entityDestroyed(entity);
            this->_entityToArchetypeMap.erase(entity);
        }
    }

    /* -------------------- Private functions -------------------- */

    void World::addComponentType(const char *&typeName) noexcept
    {
        if (this->_nextComponentType >= MAX_COMPONENTS) {
            std::cerr << "Too many component types registered.\n";
            return;
        }

        this->_componentTypes.insert({ typeName, this->_nextComponentType });
        this->_nextComponentType++;
    }

    ArchetypeID World::updateEntityArchetypeID(const EntityID &entity, const ComponentTypeID &componentType, const bool &isSet)
    {
        ArchetypeID entityArchetype = this->_entityToArchetypeMap.at(entity);

        if (isSet) {
            if (entityArchetype.test(componentType)) {
                throw DuplicateComponentTypeException("Component type added to same entity more than once.");
            }
        }

        entityArchetype.set(componentType, isSet);
        this->_entityToArchetypeMap.at(entity) = entityArchetype;

        return entityArchetype;
    }

    void World::createArchetype(const ArchetypeID &archetypeId) noexcept
    {
        if (this->_archetypes.find(archetypeId) != this->_archetypes.end()) {
            std::cerr << "Added archetype more than once.\n";
            return;
        }

        std::shared_ptr<Archetype> newArchetype = std::make_shared<Archetype>(archetypeId);

        this->_archetypes.insert({ archetypeId, newArchetype });

        for (std::pair<const char *, std::shared_ptr<System>> pair : this->_systems) {
            if ((pair.second->archetypeId & archetypeId) == pair.second->archetypeId) {
                pair.second->_archetypes.push_back(this->_archetypes.at(archetypeId));
            }
        }
    }

    void World::updateSystemArchetype(const char *&systemTypeName, ArchetypeID &systemArchetypeId) noexcept
    {
        std::shared_ptr<System> system = this->_systems.at(systemTypeName);

        system->_archetypes.clear();
        system->archetypeId = systemArchetypeId;

        for (std::pair<ArchetypeID, std::shared_ptr<Archetype>> pair : this->_archetypes) {
            if ((pair.first & systemArchetypeId) == systemArchetypeId) {
                system->_archetypes.push_back(pair.second);
            }
        }
    }
}
