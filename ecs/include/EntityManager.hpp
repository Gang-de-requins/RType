#ifndef ENTITY_MANAGER_HPP
#define ENTITY_MANAGER_HPP

#include <iostream>
#include <array>
#include <queue>
#include <exception>
#include "Macros.hpp"

namespace ecs {
    class EntityManager {
        public:
            EntityManager() :
                mAvailableEntities(),
                mSignatures(),
                mLivingEntityCount(0)
            {
                for (Entity entity = 0; entity < MAX_ENTITIES; ++entity) {
                    mAvailableEntities.push(entity);
                }
            }

            Entity CreateEntity()
            {
                if (mLivingEntityCount >= MAX_ENTITIES) {
                    std::cerr << "Too many entities in existence." << std::endl;
                    return MAX_ENTITIES + 1;
                }

                Entity id = mAvailableEntities.front();
                mAvailableEntities.pop();
                ++mLivingEntityCount;

                return id;
            }

            void DestroyEntity(Entity entity)
            {
                if (entity >= MAX_ENTITIES) {
                    std::cerr << "Entity out of range." << std::endl;
                    return;
                }

                mSignatures[entity].reset();

                mAvailableEntities.push(entity);
                --mLivingEntityCount;
            }

            void SetSignature(Entity entity, Signature signature)
            {
                if (entity >= MAX_ENTITIES) {
                    std::cerr << "Entity out of range." << std::endl;
                    return;
                }

                mSignatures[entity] = signature;
            }

            Signature GetSignature(Entity entity)
            {
                if (entity >= MAX_ENTITIES) {
                    throw std::out_of_range("Entity out of range.");
                }

                return mSignatures[entity];
            }

        private:
            std::queue<Entity> mAvailableEntities;

            std::array<Signature, MAX_ENTITIES> mSignatures;

            uint32_t mLivingEntityCount;
    };
}

#endif /* ENTITY_MANAGER_HPP */
