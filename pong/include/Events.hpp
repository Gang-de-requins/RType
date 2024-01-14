/*
** EPITECH PROJECT, 2024
** RType [WSL : Ubuntu]
** File description:
** Events
*/

#ifndef EVENTS_HPP_
#define EVENTS_HPP_

namespace ecs
{
    enum GameEvent
    {
        MoveUp,
        MoveDown,
        SpawnBonus,
        StopMoving
    };
}

namespace game
{
    #define MENU 0
    #define GAME 1
    #define END 2
    #define SETTINGS 3
}

#endif /* !EVENTS_HPP_ */
