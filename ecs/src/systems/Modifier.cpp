#include "systems/Modifier.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void ModifierSystem::update(SceneManager &sceneManager) {
        auto entities = sceneManager.view<Collision, Sprite, Controllable>(sceneManager.getCurrentScene());
        auto modifiers = sceneManager.view<Modifier, Collision, Sprite>(sceneManager.getCurrentScene());
        std::vector<Entity *> entitiesToDelete;
        std::vector<std::type_index> componentsTypes = {
            std::type_index(typeid(Acceleration)),
            std::type_index(typeid(Damage)),
            std::type_index(typeid(Health)),
            std::type_index(typeid(Rotation)),
            std::type_index(typeid(Scale)),
            std::type_index(typeid(Velocity))
        };

        for (auto &entity : entities) {
            auto &collision = sceneManager.get<Collision>(*entity);

            for (auto &modifier : modifiers) {
                auto &modifierComponent = sceneManager.get<Modifier>(*modifier);

                if (std::find(collision.collidingWith.begin(), collision.collidingWith.end(), modifier->id) != collision.collidingWith.end()) {
                    std::cout << "Found " << modifier->id << " with " << entity->id << std::endl;
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Acceleration))) != modifierComponent.modifiers.end()) {
                        std::cout << "Updating acceleration..." << std::endl;
                        applyModifier<Acceleration>(entity, componentsTypes[0], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Damage))) != modifierComponent.modifiers.end()) {
                        std::cout << "Updating damage..." << std::endl;
                        applyModifier<Damage>(entity, componentsTypes[1], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Health))) != modifierComponent.modifiers.end()) {
                        std::cout << "Updating health..." << std::endl;
                        applyModifier<Health>(entity, componentsTypes[2], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Rotation))) != modifierComponent.modifiers.end()) {
                        std::cout << "Updating rotation..." << std::endl;
                        applyModifier<Rotation>(entity, componentsTypes[3], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Scale))) != modifierComponent.modifiers.end()) {
                        std::cout << "Updating scale..." << std::endl;
                        applyModifier<Scale>(entity, componentsTypes[4], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Velocity))) != modifierComponent.modifiers.end()) {
                        std::cout << "Updating velocity..." << std::endl;
                        applyModifier<Velocity>(entity, componentsTypes[5], modifierComponent);
                    }
                }
            }
        }
    }
}
