#ifndef COMPONENT_MANAGER_ARRAY_HPP
#define COMPONENT_MANAGER_ARRAY_HPP

#include <typeindex>
#include <memory>
#include <unordered_map>
#include "IComponentArray.hpp"
#include "ComponentArray.hpp"
#include "Macros.hpp"

namespace ecs {
    class ComponentManager : public IComponentArray {
        public:
        template <typename T>
        void RegisterComponent()
        {
            const char *typeName = typeid(T).name();

            if(mComponentTypes.find(typeName) == mComponentTypes.end()) {
                std::cerr << "Registering component type more than once." << std::endl;
                return;
            }

            mComponentTypes.insert({typeName, mNextComponentType});

            mComponentArrays.insert({typeName, std::make_shared<ComponentArray<T>>()});

            ++mNextComponentType;
        }

        template <typename T>
        ComponentType GetComponentType()
        {
            const char *typeName = typeid(T).name();

            if(mComponentTypes.find(typeName) != mComponentTypes.end()) {
                std::cerr << "Component not registered before use." << std::endl;
                return;
            }

            return mComponentTypes[typeName];
        }

        template <typename T>
        void AddComponent(Entity entity, T component)
        {
            // Add a component to the array for an entity
            GetComponentArray<T>()->InsertData(entity, component);
        }

        template <typename T>
        void RemoveComponent(Entity entity)
        {
            // Remove a component from the array for an entity
            GetComponentArray<T>()->RemoveData(entity);
        }

        template <typename T>
        T &GetComponent(Entity entity)
        {
            // Get a reference to a component from the array for an entity
            return GetComponentArray<T>()->GetData(entity);
        }

        template <typename T>
        bool HasComponent(Entity entity)
        {
            // Check if an entity has a component (component exists in its array)
            return GetComponentArray<T>()->getEntityToIndexMap().find(entity) != GetComponentArray<T>()->getEntityToIndexMap().end();
        }

        void EntityDestroyed(Entity entity)
        {
            // Notify each component array that an entity has been destroyed
            // If it has a component for that entity, it will remove it
            for (auto const &pair : mComponentArrays)
            {
                auto const &component = pair.second;

                component->EntityDestroyed(entity);
            }
        }

        private:
            // Map from type string pointer to a component type
            std::unordered_map<std::type_index, ComponentType> mComponentTypes{};

            // Map from type string pointer to a component array
            std::unordered_map<std::type_index, std::shared_ptr<IComponentArray>> mComponentArrays{};

            // The component type to be assigned to the next registered component - starting at 0
            ComponentType mNextComponentType{};

            // Convenience function to get the statically casted pointer to the ComponentArray of type T.
            template <typename T>
            std::shared_ptr<ComponentArray<T>> GetComponentArray()
            {
                const char *typeName = typeid(T).name();

                assert(mComponentTypes.find(typeName) != mComponentTypes.end() && "Component not registered before use.");

                return std::static_pointer_cast<ComponentArray<T>>(mComponentArrays[typeName]);
            }
    };
}

#endif /* COMPONENT_MANAGER_ARRAY_HPP */