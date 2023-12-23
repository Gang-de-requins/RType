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

    class ModifierSystem : public ISystem {
        public:
            void update(SceneManager &sceneManager) override;
        
        private:
            template<typename T>
            void applyModifier(Entity *&entity, std::type_index &type, Modifier &modifier) {
                if (modifier.modifiers.find(type) != modifier.modifiers.end()) {
                    auto &modifierComponent = std::any_cast<T &>(modifier.modifiers.at(type));
                    auto &component = std::any_cast<T &>(entity->components[type]);

                    component += modifierComponent;

                    // if (!modifier.isPermanent) {
                    //     std::thread(&ModifierSystem::unapplyModifierHelper<T>, this, std::ref(entity), std::ref(type), std::ref(modifier), std::ref(modifierComponent)).detach();
                    // }
                }
            }

            template<typename T>
            void unapplyModifier(Entity *&entity, T &modifierComponent, std::type_index &type, Modifier &modifier) {
                // std::mutex mutex;
                // std::unique_lock<std::mutex> lock(mutex);
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
