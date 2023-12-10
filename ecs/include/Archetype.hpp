#ifndef ARCHETYPE_HPP
#define ARCHETYPE_HPP

#include <iostream>
#include <unordered_map>
#include <memory>
#include <vector>
#include <algorithm>
#include "ComponentsVector.hpp"
#include "Macros.hpp"

namespace ecs {
	class Archetype {
        public:
            Archetype(ArchetypeID archetypeId) noexcept;

            friend class World;

            ArchetypeID getArchetypeId() const noexcept;

            size_t getNumEntities() const noexcept;

            std::vector<EntityID> &getEntities() noexcept;

            template<typename T>
            std::vector<T> &getComponentVector() noexcept
            {
                const char *componentTypeName = typeid(T).name();

                return std::static_pointer_cast<ComponentVector<T>>(this->_componentVectors.at(componentTypeName))->getVector();
            }

            void addEntity(const EntityID &entity) noexcept;

            void removeEntity(const EntityID &entity) noexcept;

        private:
            ArchetypeID _archetypeId;
            size_t _numEntities;
            std::vector<EntityID> _entities;
            std::unordered_map<const char *, std::shared_ptr<IComponentVector>> _componentVectors;

            void removeComponent(const EntityID &entity, const char *&componentTypeName) noexcept;
            void entityDestroyed(const EntityID &entity) noexcept;
            std::shared_ptr<IComponentVector> getComponentVector(const char *&componentTypeName) noexcept;
            void transferComponents(const EntityID &entity, std::shared_ptr<Archetype> newArchetype) noexcept;

            template<typename T>
            void addComponent(EntityID entity, T component) noexcept
            {
                const char *componentTypeName = typeid(T).name();

                if (this->_componentVectors.find(componentTypeName) == this->_componentVectors.end()) {
                    this->_componentVectors.insert({ componentTypeName, std::make_shared<ComponentVector<T>>() });
                }

                std::static_pointer_cast<ComponentVector<T>>(this->_componentVectors.at(componentTypeName))->addComponent(entity, component);
            }

            template<typename T>
            void updateComponent(EntityID entity, T component) noexcept
            {
                const char *componentTypeName = typeid(T).name();

                if (this->_componentVectors.find(componentTypeName) == this->_componentVectors.end()) {
                    std::cerr << "Component vector does not exist." << std::endl;
                    return;
                }

                std::static_pointer_cast<ComponentVector<T>>(this->_componentVectors.at(componentTypeName))->updateComponent(entity, component);
            }
	};
}

#endif /* ARCHETYPE_HPP */
