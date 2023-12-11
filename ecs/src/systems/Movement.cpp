#include "systems/Movement.hpp"

namespace ecs {
    void MovementSystem::update(World &world) {
        for (std::shared_ptr<Archetype> archetype : this->_archetypes) {
            std::vector<Position> &positions = archetype->getComponentVector<Position>();
            std::vector<Velocity> &velocities = archetype->getComponentVector<Velocity>();
            std::vector<Acceleration> &accelerations = archetype->getComponentVector<Acceleration>();

            for (std::size_t i = 0; i < positions.size(); ++i) {
                velocities[i].x += accelerations[i].x;
                velocities[i].y += accelerations[i].y;

                if (velocities[i].x > accelerations[i].maxSpeed)
                    velocities[i].x = accelerations[i].maxSpeed;
                else if (velocities[i].x < -accelerations[i].maxSpeed)
                    velocities[i].x = -accelerations[i].maxSpeed;

                if (velocities[i].y > accelerations[i].maxSpeed)
                    velocities[i].y = accelerations[i].maxSpeed;
                else if (velocities[i].y < -accelerations[i].maxSpeed)
                    velocities[i].y = -accelerations[i].maxSpeed;

                positions[i].x += velocities[i].x;
                positions[i].y += velocities[i].y;
            }
        }
    }
}
