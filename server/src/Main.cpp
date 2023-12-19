/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include "../include/ServerRooms.hpp"
#include "Rtype.hpp"
#include "Message.hpp"

void receiveMessageThread(std::shared_ptr<serverGame::Rtype> rtype)
{
	while(true)
	{
		serverGame::Message msg;
        rtype->server.receiveMessage(msg);
		rtype->mutex.lock();
		rtype->msgList.push_back(msg);
		rtype->mutex.unlock();
	}
}

void sendGameStateThread(std::shared_ptr<serverGame::Rtype> rtype) {
    while (true) {
        rtype->sendGameState();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 32));
    }
}


int main()
{
    // serverGame::ServerRooms Rooms;
    // Rooms.start();
    std::shared_ptr<serverGame::Rtype> rtype = std::make_shared<serverGame::Rtype>();
    std::thread receive(receiveMessageThread, rtype);
    std::thread send(sendGameStateThread, rtype);
    rtype->run();
    return 0;
}
