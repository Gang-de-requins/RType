#include "Archetype.hpp"

namespace ecs {
	Archetype::Archetype(ArchetypeID archetypeId) noexcept :
	_archetypeId { archetypeId },
	_numEntities { 0 },
	_entities {}
	{
	}

	ArchetypeID Archetype::getArchetypeId() const noexcept
	{
		return this->_archetypeId;
	}

	size_t Archetype::getNumEntities() const noexcept
	{
		return this->_numEntities;
	}

	std::vector<EntityID> &Archetype::getEntities() noexcept
	{
		return this->_entities;
	}

	void Archetype::addEntity(const EntityID &entity) noexcept
	{
		this->_entities.push_back(entity);
		this->_numEntities++;
	}

	void Archetype::removeEntity(const EntityID &entity) noexcept
	{
		this->_entities.erase(std::remove(this->_entities.begin(), this->_entities.end(), entity), this->_entities.end());
		this->_numEntities--;
	}

	void Archetype::removeComponent(const EntityID &entity, const char *&componentTypeName) noexcept
	{
		this->_componentVectors.at(componentTypeName)->removeComponent(entity);
	}

	void Archetype::entityDestroyed(const EntityID &entity) noexcept
	{
		for (std::pair<const char *, std::shared_ptr<IComponentVector>> pair : this->_componentVectors) {
			pair.second->entityDestroyed(entity);
		}
		this->removeEntity(entity);
	}

	std::shared_ptr<IComponentVector> Archetype::getComponentVector(const char *&componentTypeName) noexcept
	{
		return this->_componentVectors.at(componentTypeName);
	}

	void Archetype::transferComponents(const EntityID &entity, std::shared_ptr<Archetype> newArchetype) noexcept
	{
		for (std::pair<const char *, std::shared_ptr<IComponentVector>> pair : this->_componentVectors) {
			if (newArchetype->_componentVectors.count(pair.first) == 0) {
				newArchetype->_componentVectors.insert({ pair.first, pair.second->createEmptyClone() });
			}

			pair.second->transferComponents(entity, newArchetype->getComponentVector(pair.first));

			this->removeComponent(entity, pair.first);
		}
	}
}
