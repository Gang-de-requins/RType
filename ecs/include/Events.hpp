#ifndef EVENTS_HPP
#define EVENTS_HPP

#include <cstddef>
#include <vector>
#include "Entity.hpp"

namespace ecs {
    enum EventType {
        Collisionnnnnn,
        Destroy,
        Input,
        Spawn,
        Timer,
        Audio
    };

    enum Event {
        Overlap,
        MoveUp,
        MoveDown,
        MoveLeft,
        MoveRight,
        StopMoving,
        Shoot,
        SpawnEnemy,
        SpawnPlayer,
        SpawnEnemyBullet,
        SpawnPlayerBullet,
        PlayerDeath,
        EnemyDeath,
        BulletDeath,
        EnemyBulletDeath,
        ModifierDisparition,
    };

    struct EventData {
        Event event;
        std::vector<Entity *> entities;
    };
}

#endif /* EVENTS_HPP */
