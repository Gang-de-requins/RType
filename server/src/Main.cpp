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
		ecs::Buffer buffer;
        rtype->server.receiveMessage(buffer);
		rtype->mutex.lock();
		rtype->bufferList.push_back(buffer);
		rtype->mutex.unlock();
	}
}

void sendGameStateThread(std::shared_ptr<serverGame::Rtype> rtype) {
    while (true) {
        rtype->sendGameState();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 32));
    }
}


int checkArguments(int ac, char const * const *av)
{
    if (ac != 2) {
        std::cerr << "Usage: ./rtype_server <port>" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        int port = std::stoi(av[1]);

        if (port < 0 || port > 65535)
            throw std::invalid_argument("Port must be between 0 and 65535");
    } catch (std::invalid_argument const &e) {
        std::cerr << "Invalid port: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int ac, char const * const *av)
{
    // serverGame::ServerRooms Rooms;
    // Rooms.start();
    
    if (checkArguments(ac, av) == EXIT_FAILURE)
        return 84;

    std::shared_ptr<serverGame::Rtype> rtype = std::make_shared<serverGame::Rtype>(std::stoi(av[1]));
    std::thread receive(receiveMessageThread, rtype);
    std::thread send(sendGameStateThread, rtype);
    rtype->run();
    return 0;
}
