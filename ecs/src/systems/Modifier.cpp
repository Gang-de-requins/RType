#include "systems/Modifier.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void ModifierSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();
        int index = 0;
        std::vector<int> eventsToRemove = {};

        for (auto &event : scene.events.at(EventType::Collisionnnnnn)) {
            if (event.event == Event::ApplyModifier) {
                std::vector<std::type_index> componentsTypes = {
                    std::type_index(typeid(Acceleration)),
                    std::type_index(typeid(Damage)),
                    std::type_index(typeid(Health)),
                    std::type_index(typeid(Rotation)),
                    std::type_index(typeid(Scale)),
                    std::type_index(typeid(Velocity))
                };
                Modifier &modifier = sceneManager.get<Modifier>(*event.entities.at(0));
                Entity &entity = *event.entities.at(1);
                bool modifierApplied = false;

                for (auto &component : entity.components) {
                    if (this->hasModifier(modifier, componentsTypes[0]) && component.first == componentsTypes[0]) {
                        modifierApplied = true;
                        this->applyModifier<Acceleration>(entity, componentsTypes[0], modifier);
                    }
                    if (this->hasModifier(modifier, componentsTypes[1]) && component.first == componentsTypes[1]) {
                        modifierApplied = true;
                        this->applyModifier<Damage>(entity, componentsTypes[1], modifier);
                    }
                    if (this->hasModifier(modifier, componentsTypes[2]) && component.first == componentsTypes[2]) {
                        modifierApplied = true;
                        this->applyModifier<Health>(entity, componentsTypes[2], modifier);
                    }
                    if (this->hasModifier(modifier, componentsTypes[3]) && component.first == componentsTypes[3]) {
                        modifierApplied = true;
                        this->applyModifier<Rotation>(entity, componentsTypes[3], modifier);
                    }
                    if (this->hasModifier(modifier, componentsTypes[4]) && component.first == componentsTypes[4]) {
                        modifierApplied = true;
                        this->applyModifier<Scale>(entity, componentsTypes[4], modifier);
                    }
                    if (this->hasModifier(modifier, componentsTypes[5]) && component.first == componentsTypes[5]) {
                        modifierApplied = true;
                        this->applyModifier<Velocity>(entity, componentsTypes[5], modifier);
                    }
                }
                if (modifierApplied) {
                    scene.events[EventType::Destroy].push_back({
                        Event::ModifierDisparition,
                        {event.entities.at(0)}
                    });
                }
                eventsToRemove.push_back(index);
            }
            index++;
        }

        for (auto &event : eventsToRemove) {
            scene.events.at(EventType::Collisionnnnnn).erase(scene.events.at(EventType::Collisionnnnnn).begin() + event);
        }
    }
}
