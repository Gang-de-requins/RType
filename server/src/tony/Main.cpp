/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include "../include/ServerRooms.hpp"
#include "Rtype.hpp"
#include "Message.hpp"

void receiveMessageThread(serverGame::Rtype &rtype)
{
	while(true)
	{
		serverGame::Message msg;
        rtype.server.receiveMessage(msg);
		rtype.mutex.lock();
		rtype.msgList.push_back(msg);
		rtype.mutex.unlock();
	}
}

int main()
{

    serverGame::Rtype rtype;
    std::thread receive(receiveMessageThread, std::ref(rtype));
    rtype.run();
    return EXIT_SUCCESS;
}
