#ifndef GAME_HPP_
#define GAME_HPP_

    #include <ctime>
    #include <chrono>
    #include "raylib.h"
    #include "../../ecs/include/World.hpp"

namespace Client {
    class Game {
        public:

            Game();
            ~Game();
            int launchGame(void);
            void connectServer(void);
            void disconnectServer(void);

        protected:
        private:
            ecs::World _ecs;
            ecs::MovementSystem _movementSystem;
            ecs::ControllableSystem _controllableSystem;
            ecs::SpriteSystem _spriteSystem;
            ecs::AnimationSystem _animationSystem;
            ecs::MusicSystem _musicSystem;
            ecs::TextSystem _textSystem;
    };
}

#endif /* !GAME_HPP_ */
