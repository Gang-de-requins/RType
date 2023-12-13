#ifndef ISYSTEM_HPP
#define ISYSTEM_HPP

namespace ecs {
    class World;

	class ISystem {
        public:
            virtual ~ISystem() = default;
            virtual void update(World &world) = 0;
    };
}

#endif /* ISYSTEM_HPP */
