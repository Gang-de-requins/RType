#ifndef GAME_HPP_
#define GAME_HPP_

    #include <ctime>
    #include <chrono>
    #include "raylib.h"

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
    };
}

#endif /* !GAME_HPP_ */
