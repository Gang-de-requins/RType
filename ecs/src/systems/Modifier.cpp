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
                bool modifierApplied = false;

                if (std::find(collision.collidingWith.begin(), collision.collidingWith.end(), modifier->id) != collision.collidingWith.end()) {
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Acceleration))) != modifierComponent.modifiers.end()) {
                        modifierApplied = true;
                        applyModifier<Acceleration>(entity, componentsTypes[0], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Damage))) != modifierComponent.modifiers.end()) {
                        modifierApplied = true;
                        applyModifier<Damage>(entity, componentsTypes[1], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Health))) != modifierComponent.modifiers.end()) {
                        modifierApplied = true;
                        applyModifier<Health>(entity, componentsTypes[2], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Rotation))) != modifierComponent.modifiers.end()) {
                        modifierApplied = true;
                        applyModifier<Rotation>(entity, componentsTypes[3], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Scale))) != modifierComponent.modifiers.end()) {
                        modifierApplied = true;
                        applyModifier<Scale>(entity, componentsTypes[4], modifierComponent);
                    }
                    if (modifierComponent.modifiers.find(std::type_index(typeid(Velocity))) != modifierComponent.modifiers.end()) {
                        modifierApplied = true;
                        applyModifier<Velocity>(entity, componentsTypes[5], modifierComponent);
                    }

                    if (modifierApplied) {
                        entitiesToDelete.emplace_back(modifier);
                    }
                }
            }
        }

        for (auto &entity : entitiesToDelete) {
            //sceneManager.destroyEntity(sceneManager.getCurrentScene(), *entity);
        }
    }
}
