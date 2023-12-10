#include "systems/Movement.hpp"

namespace ecs {
    void MovementSystem::update(World &world) {
        for (std::shared_ptr<Archetype> archetype : this->_archetypes) {
            std::vector<Position> &positions = archetype->getComponentVector<Position>();
            std::vector<Velocity> &velocities = archetype->getComponentVector<Velocity>();

            for (std::size_t i = 0; i < positions.size(); ++i) {
                positions[i].x += velocities[i].x;
                positions[i].y += velocities[i].y;
            }
        }
    }
}
