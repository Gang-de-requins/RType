#include "systems/Life.hpp"
#include "SceneManager.hpp"

namespace ecs {
    void LifeSystem::update(SceneManager &sceneManager) {
        ecs::Scene &scene = sceneManager.getCurrentScene();
        int index = 0;
        std::vector<int> eventsToRemove = {};

        for (auto &event : scene.events.at(EventType::Collisionnnnnn)) {
            if (event.event == Event::DealDamage) {
                Damage &damage = sceneManager.get<Damage>(*event.entities.at(0));
                Health &health = sceneManager.get<Health>(*event.entities.at(1));

                health.health -= damage.damage;

                if (health.health <= 0) {
                    scene.events[EventType::Destroy].push_back({
                        Event::EntityDestroyed,
                        {event.entities.at(1)}
                    });
                }
                scene.events[EventType::Destroy].push_back({
                    Event::EntityDestroyed,
                    {event.entities.at(0)}
                });
                eventsToRemove.push_back(index);
            }
            index++;
        }

        for (auto &event : eventsToRemove) {
            scene.events.at(EventType::Collisionnnnnn).erase(scene.events.at(EventType::Collisionnnnnn).begin() + event);

            for (auto &i : eventsToRemove) {
                if (i > event) {
                    i--;
                }
            }
        }
    }
}
