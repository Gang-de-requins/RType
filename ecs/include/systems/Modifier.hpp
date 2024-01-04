#ifndef MODIFIER_SYSTEM_HPP
#define MODIFIER_SYSTEM_HPP

#include <vector>
#include <algorithm>
#include "Entity.hpp"
#include "components/Components.hpp"
#include "ISystem.hpp"
#include "SceneManager.hpp"

namespace ecs {
    class SceneManager;

    /**
     * @class ModifierSystem
     * @brief Modifier System class
     * 
     * @details
     * Part of the Entity Component System, the ModifierSystem class is responsible for applying and managing modifiers to entities. It utilizes the Modifier component to adjust other components' values temporarily or permanently.
     * 
     * Inherits from ISystem and overrides the update method to implement logic for applying and removing modifiers.
     */
    class ModifierSystem : public ISystem {
        public:
            /**
             * @brief Updates the modifier states of entities
             * 
             * @param sceneManager Reference to the SceneManager which manages the current scene and its entities.
             * 
             * This method iterates through entities with Modifier components, applying or removing modifiers based on the current game state and logic.
             */
            void update(SceneManager &sceneManager) override;

        private:
            /**
             * @brief Applies a modifier to an entity's component
             * 
             * @tparam T The component type to which the modifier is applied.
             * @param entity Pointer to the entity being modified.
             * @param type The type index of the component.
             * @param modifier The Modifier component of the entity.
             * 
             * This method applies the specified modifier to the specified component of an entity if the modifier exists.
             */
            template<typename T>
            void applyModifier(Entity *&entity, std::type_index &type, Modifier &modifier) {
                if (modifier.modifiers.find(type) != modifier.modifiers.end()) {
                    auto &modifierComponent = std::any_cast<T &>(modifier.modifiers.at(type));
                    auto &component = std::any_cast<T &>(entity->components[type]);

                    component += modifierComponent;
                }
            }

            /**
             * @brief Unapplies a modifier from an entity's component
             * 
             * @tparam T The component type from which the modifier is removed.
             * @param entity Pointer to the entity being modified.
             * @param modifierComponent The specific modifier to be unapplied.
             * @param type The type index of the component.
             * @param modifier The Modifier component of the entity.
             * 
             * This method removes the specified modifier from the specified component of an entity.
             */
            template<typename T>
            void unapplyModifier(Entity *&entity, T &modifierComponent, std::type_index &type, Modifier &modifier) {
                std::cout << "Casting modifier..." << std::endl;
                try {
                    for (auto &component : entity->components) {
                        std::cout << "Component: " << component.first.name() << std::endl;
                    }
                    auto &component = std::any_cast<T &>((*entity).components.at(type));

                    std::cout << "Unapplying modifier..." << std::endl;
                    component -= modifierComponent;
                    std::cout << "Modifier unapplied" << std::endl;
                } catch (const std::exception &e) {
                    std::cout << "Error: " << e.what() << std::endl;
                }
            }

            /**
             * @brief Helper function to unapply a modifier after a delay
             * 
             * @tparam T The component type from which the modifier is removed.
             * @param entity Pointer to the entity being modified.
             * @param type The type index of the component.
             * @param modifier The Modifier component of the entity.
             * @param modifierComponent The specific modifier to be unapplied.
             * 
             * This method waits for the duration specified in the modifier before calling unapplyModifier.
             */
            template<typename T>
            void unapplyModifierHelper(Entity *&entity, std::type_index &type, Modifier &modifier, T &modifierComponent) {
                std::cout << "Duration: " << modifier.duration << std::endl;
                std::this_thread::sleep_for(std::chrono::milliseconds(static_cast<int>(modifier.duration)));

                std::cout << "Unapplying modifier..." << std::endl;
                unapplyModifier<T>(entity, modifierComponent, type, modifier);
            }
    };
}

#endif /* MODIFIER_SYSTEM_HPP */
