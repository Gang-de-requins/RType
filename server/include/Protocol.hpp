#ifndef PROTOCOL_HPP
#define PROTOCOL_HPP

#include <iostream>
#include <string>
#include <boost/asio.hpp>
#include <boost/serialization/string.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace rtype {
    enum class PacketType {
        UNKNOWN,
        CONNECT,
        DISCONNECT,
        CREATE,
        DESTROY,
        UPDATE,
        INPUT,
        GAME_STATE
    };

    struct Packet {
        PacketType type;
        std::string data;
    };

    template <typename Archive>
    void serialize(Archive &ar, Packet &packet, const unsigned int version)
    {
        static_cast<void>(version);
        ar & packet.type;
        ar & packet.data;
    }
}

#endif /* PROTOCOL_HPP */
