#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <cstddef>
#include <vector>
#include "Entity.hpp"

namespace ecs {
    enum EventType {
        Collisionnnnnn,
        Death,
        Input,
        Spawn,
        Timer
    };

    enum Event {
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight,
        StopMoving
    };

    struct EventData {
        Event event;
        std::vector<Entity *> entities;
    };
}

#endif /* EVENTS_HPP */
