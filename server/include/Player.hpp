#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <asio.hpp>

namespace server {
    class Player {
        public:
            Player(std::string name, asio::ip::udp::endpoint endpoint) : _name(name), _endpoint(endpoint) {}


        private:
            std::string _name;
    };
}

#endif /* PLAYER_HPP */
