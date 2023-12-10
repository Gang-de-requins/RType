#ifndef SYSTEM_HPP
#define SYSTEM_HPP

#include <vector>
#include <memory>
#include "Archetype.hpp"
#include "Macros.hpp"

namespace ecs {
    class World;

	class System {
        public:
            friend class World;
            std::vector<std::shared_ptr<Archetype>> _archetypes;
            virtual void update(World &world) = 0;
        private:
            ArchetypeID archetypeId;
    };
}

#endif /* SYSTEM_HPP */
