#ifndef COMPONENT_ARRAY_HPP
#define COMPONENT_ARRAY_HPP

#include <iostream>
#include <unordered_map>
#include <array>
#include <exception>
#include "IComponentArray.hpp"
#include "Macros.hpp"

namespace ecs {
    template <typename T>
    class ComponentArray : public IComponentArray {
        public:
            void InsertData(Entity entity, T component)
            {
                if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end()) {
                    std::cerr << "Component added to same entity more than once." << std::endl;
                    return;
                }

                size_t newIndex = mSize;
                mEntityToIndexMap[entity] = newIndex;
                mIndexToEntityMap[newIndex] = entity;
                mComponentArray[newIndex] = component;
                ++mSize;
            }

            void RemoveData(Entity entity)
            {
                if (mEntityToIndexMap.find(entity) == mEntityToIndexMap.end()) {
                    std::cerr << "Removing non-existent component." << std::endl;
                    return;
                }

                size_t indexOfRemovedEntity = mEntityToIndexMap[entity];
                size_t indexOfLastElement = mSize - 1;
                mComponentArray[indexOfRemovedEntity] = mComponentArray[indexOfLastElement];

                Entity entityOfLastElement = mIndexToEntityMap[indexOfLastElement];
                mEntityToIndexMap[entityOfLastElement] = indexOfRemovedEntity;
                mIndexToEntityMap[indexOfRemovedEntity] = entityOfLastElement;

                mEntityToIndexMap.erase(entity);
                mIndexToEntityMap.erase(indexOfLastElement);

                --mSize;
            }

            T &GetData(Entity entity)
            {
                if (mEntityToIndexMap.find(entity) == mEntityToIndexMap.end()) {
                    throw std::runtime_error("Retrieving non-existent component.");
                }

                return mComponentArray[mEntityToIndexMap[entity]];
            }

            void EntityDestroyed(Entity entity) override
            {
                if (mEntityToIndexMap.find(entity) != mEntityToIndexMap.end())
                {
                    // Remove the entity's component if it existed
                    RemoveData(entity);
                }
            }

            std::unordered_map<Entity, size_t> getEntityToIndexMap()
            {
                return mEntityToIndexMap;
            }

        private:
            // The packed array of components (of generic type T),
            // set to a specified maximum amount, matching the maximum number
            // of entities allowed to exist simultaneously, so that each entity
            // has a unique spot.
            std::array<T, MAX_ENTITIES> mComponentArray;

            // Map from an entity ID to an array index.
            std::unordered_map<Entity, size_t> mEntityToIndexMap;

            // Map from an array index to an entity ID.
            std::unordered_map<size_t, Entity> mIndexToEntityMap;

            // Total size of valid entries in the array.
            size_t mSize;
    };
}

#endif /* COMPONENT_ARRAY_HPP */
