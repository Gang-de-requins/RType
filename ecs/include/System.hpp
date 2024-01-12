#ifndef SYSTEMHPP
#define SYSTEMHPP

#include "Macros.hpp"
#include <set>

namespace ecs {
    class System
    {
    public:
        std::set<Entity> mEntities;
    };
}

#endif /* SYSTEMHPP */