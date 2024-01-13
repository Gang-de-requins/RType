#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <asio.hpp>

namespace server {
    class Player {
        public:
            Player(std::string name, asio::ip::udp::endpoint endpoint) : _name(name), _endpoint(endpoint) {}
            ~Player() {}

            std::string getName() const { return _name; }
            asio::ip::udp::endpoint getEndpoint() const { return _endpoint; }

        private:
            std::string _name;
            asio::ip::udp::endpoint _endpoint;
    };
}

#endif /* PLAYER_HPP */
