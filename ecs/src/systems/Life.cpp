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
                    if (sceneManager.has<Controllable>(*event.entities.at(1))) {
                        scene.events[EventType::Destroy].push_back({
                            Event::PlayerDeath,
                            {event.entities.at(1)}
                        });
                    } else {
                        scene.events[EventType::Destroy].push_back({
                            Event::EnemyDeath,
                            {event.entities.at(1)}
                        });
                    }
                }
                scene.events[EventType::Destroy].push_back({
                    Event::EnemyDeath,
                    {event.entities.at(0)}
                });
                eventsToRemove.push_back(index);
            }
            index++;
        }

        for (auto &event : eventsToRemove) {
            scene.events.at(EventType::Collisionnnnnn).erase(scene.events.at(EventType::Collisionnnnnn).begin() + event);
        }
    }
}
