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
        Audio,
        KeyboardInput
    };

    enum Event {
        Overlap,
        Shoot,
        PlayerDeath,
        EnemyDeath,
        BulletDeath,
        EnemyBulletDeath,
        ModifierDisparition,
        PlaySound,
        PlayMusic,
        StopMusic,
        UpdateMusic,
        PauseMusic,
        ResumeMusic,
        SetVolumeMusic,
        DealDamage,
        ApplyModifier,
    };

    struct EventData {
        int event;
        std::vector<Entity *> entities;
    };
}

#endif /* EVENTS_HPP */
