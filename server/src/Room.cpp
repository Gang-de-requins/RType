#include "Room.hpp"

namespace rtype {
    Room::Room(const int maxPlayers) :
    m_maxPlayers(maxPlayers),
    m_isOpen(true)
    {
    }

    bool Room::isOpen() const
    {
        return m_isOpen;
    }

    bool Room::isFull() const
    {
        return m_players.size() == m_maxPlayers;
    }

    void Room::close()
    {
        m_isOpen = false;
    }

    void Room::open()
    {
        m_isOpen = true;
    }
}
