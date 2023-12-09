#ifndef COMPONENTS_VECTOR_HPP
#define COMPONENTS_VECTOR_HPP

#include <iostream>
#include <vector>
#include <unordered_map>
#include <memory>
#include "Macros.hpp"

class IComponentVector {
    public:
        virtual ~IComponentVector() = default;
        virtual void removeComponent(const EntityID& entity) noexcept = 0;
        virtual void transferComponents(const EntityID& entity, std::shared_ptr<IComponentVector> newVector) noexcept = 0;
        virtual void entityDestroyed(const EntityID& entity) noexcept = 0;
        virtual std::shared_ptr<IComponentVector> createEmptyClone() const noexcept = 0;
};

template<typename T>
class ComponentVector : public IComponentVector {
    public:
        void addComponent(const EntityID& entity, const T& component) noexcept
        {
            if (this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end()) {
                std::cerr << "Component type added to same entity more than once.\n";
                return;
            }

            size_t index = this->_componentVector.size();
            this->_componentVector.push_back(component);
            this->_entityToIndexMap.insert({ entity, index });
            this->_indexToEntityMap.insert({ index, entity });
        }

        void updateComponent(const EntityID &entity, const T& component) noexcept
        {
            if (this->_entityToIndexMap.find(entity) == this->_entityToIndexMap.end()) {
                std::cerr << "Attempting to update component that does not exist.\n";
                return;
            }

            this->_componentVector[this->_entityToIndexMap.at(entity)] = component;
        }

        void removeComponent(const EntityID& entity) noexcept override
        {
            if (this->_entityToIndexMap.find(entity) == this->_entityToIndexMap.end()) {
                std::cerr << "Attempting to remove component that does not exist.\n";
                return;
            }

            size_t indexOfRemovedEntity = this->_entityToIndexMap.at(entity);
            size_t indexOfLastEntity = this->_componentVector.size() - 1;

            this->_componentVector[indexOfRemovedEntity] = this->_componentVector[indexOfLastEntity];
            this->_componentVector.pop_back();

            EntityID lastEntity = this->_indexToEntityMap[indexOfLastEntity];
            this->_entityToIndexMap.at(lastEntity) = indexOfRemovedEntity;
            this->_indexToEntityMap.at(indexOfRemovedEntity) = lastEntity;

            this->_entityToIndexMap.erase(entity);
            this->_indexToEntityMap.erase(indexOfLastEntity);
        }

        std::vector<T> &getVector() noexcept
        {
            return this->_componentVector;
        }

        T &getComponent(const EntityID &entity)
        {
            if (this->_entityToIndexMap.find(entity) == this->_entityToIndexMap.end()) {
                throw std::out_of_range("Attempting to retrieve component that does not exist.");
            }

            return this->_componentVector[this->_entityToIndexMap.at(entity)];
        }

        void entityDestroyed(const EntityID &entity) noexcept
        {
            if (this->_entityToIndexMap.find(entity) != this->_entityToIndexMap.end()) {
                this->removeComponent(entity);
            }
        }

        std::shared_ptr<IComponentVector> createEmptyClone() const noexcept
        {
            return std::make_shared<ComponentVector<T>>();
        }

        void transferComponents(const EntityID &entity, std::shared_ptr<IComponentVector> newVector) noexcept override
        {
            std::shared_ptr<ComponentVector<T>> newPtr = std::static_pointer_cast<ComponentVector<T>>(newVector);
            newPtr->addComponent(entity, this->getComponent(entity));
        }

    private:
        std::vector<T> _componentVector;
        std::unordered_map<EntityID, size_t> _entityToIndexMap;
        std::unordered_map<size_t, EntityID> _indexToEntityMap;
};

#endif /* COMPONENTS_VECTOR_HPP */
