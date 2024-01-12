#ifndef ICOMPONENT_ARRAY_HPP
#define ICOMPONENT_ARRAY_HPP

#include "Macros.hpp"

namespace ecs {
    class IComponentArray {
        public:
            virtual ~IComponentArray() = default;
            virtual void EntityDestroyed(Entity entity) = 0;
    };
}

#endif /* ICOMPONENT_ARRAY_HPP */
