#ifndef EVENTS_CUSTOM_HPP
#define EVENTS_CUSTOM_HPP

#include "Events.hpp"

namespace ecs {
    enum CustomEvent {
        MoveUp = 500,
        MoveDown,
        MoveLeft,
        MoveRight,
        StopMoving,
        SpawnEnemy,
        SpawnPlayer,
        SpawnEnemyBullet,
        SpawnPlayerBullet,
        // BulletDeath,
    };
}

#endif /* EVENTS_CUSTOM_HPP */
