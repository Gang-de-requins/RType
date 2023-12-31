#ifndef ROOM_HPP
#define ROOM_HPP

#include <iostream>
#include <asio.hpp>
#include <unordered_map>
#include <tuple>

namespace rtype {
    class Room {
        int m_maxPlayers;
        bool m_isOpen;
        std::unordered_map<int, std::tuple<asio::ip::udp::endpoint, std::string, bool>> m_players;

        public:
            Room(const int maxPlayers = 4);

            bool isOpen() const;
            bool isFull() const;
            void close();
            void open();
    };
}

#endif /* ROOM_HPP */
