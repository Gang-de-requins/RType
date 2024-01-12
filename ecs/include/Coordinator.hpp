#ifndef COORDINATOR_HPP_
#define COORDINATOR_HPP_

#include <memory>
#include "Macros.hpp"
#include "SystemManager.hpp"
#include "EntityManager.hpp"
#include "ComponentManager.hpp"
#include "components/Tag.hpp"

namespace ecs {
    class Coordinator {
        public:
            void Init() {
                // Create pointers to each manager
                mComponentManager = std::make_unique<ComponentManager>();
                mEntityManager = std::make_unique<EntityManager>();
                mSystemManager = std::make_unique<SystemManager>();
            }

            // Entity methods
            Entity CreateEntity()
            {
                return mEntityManager->CreateEntity();
            }

            void DestroyEntity(Entity entity)
            {
                mEntityManager->DestroyEntity(entity);

                mComponentManager->EntityDestroyed(entity);

                mSystemManager->EntityDestroyed(entity);
            }

            // Component methods
            template <typename T>
            void RegisterComponent()
            {
                mComponentManager->RegisterComponent<T>();
            }

            template <typename T>
            void AddComponent(Entity entity, T component)
            {
                mComponentManager->AddComponent<T>(entity, component);

                auto signature = mEntityManager->GetSignature(entity);
                signature.set(mComponentManager->GetComponentType<T>(), true);
                mEntityManager->SetSignature(entity, signature);

                mSystemManager->EntitySignatureChanged(entity, signature);
            }

            template <typename T>
            void RemoveComponent(Entity entity)
            {
                mComponentManager->RemoveComponent<T>(entity);

                auto signature = mEntityManager->GetSignature(entity);
                signature.set(mComponentManager->GetComponentType<T>(), false);
                mEntityManager->SetSignature(entity, signature);

                mSystemManager->EntitySignatureChanged(entity, signature);
            }

            template <typename T>
            T &GetComponent(Entity entity)
            {
                return mComponentManager->GetComponent<T>(entity);
            }

            template <typename T>
            ComponentType GetComponentType()
            {
                return mComponentManager->GetComponentType<T>();
            }

            template <typename T>
            bool HasComponent(Entity entity)
            {
                return mComponentManager->HasComponent<T>(entity);
            }

            int GetNBEntitiesWithTag(std::string tag)
            {
                int nbEntities = 0;

                for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
                {
                    if (HasComponent<Tag>(entity) && GetComponent<Tag>(entity).tag == tag)
                    {
                        nbEntities++;
                    }
                }
                return nbEntities;
            }

            int GetNBEntitiiesWithTagContaining(std::string tag)
            {
                int nbEntities = 0;

                for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
                {
                    if (HasComponent<Tag>(entity) && GetComponent<Tag>(entity).tag.find(tag) != std::string::npos)
                    {
                        nbEntities++;
                    }
                }
                return nbEntities;
            }

            Entity GetEntityByTag(std::string tag)
            {
                for (Entity entity = 0; entity < MAX_ENTITIES; ++entity)
                {
                    if (HasComponent<Tag>(entity) && GetComponent<Tag>(entity).tag == tag)
                    {
                        return entity;
                    }
                }
                return -1;
            }

            // System methods
            template <typename T>
            std::shared_ptr<T> RegisterSystem()
            {
                return mSystemManager->RegisterSystem<T>();
            }

            template <typename T>
            void SetSystemSignature(Signature signature)
            {
                mSystemManager->SetSignature<T>(signature);
            }

        private:
            std::unique_ptr<ComponentManager> mComponentManager;
            std::unique_ptr<EntityManager> mEntityManager;
            std::unique_ptr<SystemManager> mSystemManager;
        };
}

#endif /* !COORDINATOR_HPP_ */
