#include "Game.hpp"

namespace rtype_client {
    Game::Game(const std::string &host, const unsigned short portUDP, const std::string &name) :
    m_network(host, portUDP, name)
    {
    }

    Game::~Game()
    {
    }

    void Game::run()
    {
        this->m_network.run();
    }
}
