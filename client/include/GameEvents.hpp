#ifndef GAME_EVENTS_HPP
#define GAME_EVENTS_HPP

namespace ecs {
	enum GameEvent {
        MoveUp = 100,
        MoveDown,
        MoveLeft,
        MoveRight,
        StopMoving,
        SpawnEnemy,
        SpawnPlayer,
        SpawnEnemyBullet,
        SpawnPlayerBullet,
	};
}

#endif /* GAME_EVENTS_HPP */
