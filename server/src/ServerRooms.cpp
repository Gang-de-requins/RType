/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include <iostream>
#include <boost/asio.hpp>
#include "../include/ServerRooms.hpp"
#include "Rtype.hpp"

serverGame::ServerRooms::ServerRooms()
{
    this->port = 4242;
    this->server.setupServer(port);
    this->port += 10
}

serverGame::ServerRooms::~ServerRooms()
{

}

void serverGame::ServerRooms::start()
{
    while(true)
    {
        ecs::Buffer buffer;
        this->server.receiveMessage(buffer);

        ecs::MessageType messageType = buffer.readMessageType();
        std::string messageString = buffer.readString();
        boost::asio::ip::udp::endpoint endpoint = buffer.getEndpoint();

        switch (messageType)
        {
            case ecs::MessageType::CreateRoom:
                this->createRoom(messageString);
                break;

            case ecs::MessageType::GetRooms:
                this->getRooms(endpoint);
                break;
        }
    }
}

void serverGame::ServerRooms::createRoom(std::string roomName)
{
    std::shared_ptr<serverGame::Rtype> rtype = std::make_shared<serverGame::Rtype>(this->port);
    rtype->name = roomName;
    this->threadPool.push_back(std::thread(rtypeThread, rtype));
    // créer une liste pour stocker les infos pour pouvoir les envoyers aux clients
    this->port += 2;
}

void serverGame::ServerRooms::getRooms(boost::asio::ip::udp::endpoint endpoint)
{

}

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

void rtypeThread(std::shared_ptr<serverGame::Rtype> rtype)
{
    std::thread receive(receiveMessageThread, rtype);
    std::thread send(sendGameStateThread, rtype);
    rtype->run();
}