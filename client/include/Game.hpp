#ifndef GAME_HPP
#define GAME_HPP

#include "Network.hpp"

namespace rtype_client {
    class Game {
        Network m_network;

        public:
            Game(const std::string &host, const unsigned short portUDP, const std::string &name);
            ~Game();

            void run();
    };
}

#endif /* GAME_HPP */
