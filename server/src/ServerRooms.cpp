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
    this->port += 10;
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
            default:
                break;
        }
    }
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

void serverGame::ServerRooms::createRoom(std::string roomName) {
        std::shared_ptr<serverGame::Rtype> rtype = std::make_shared<serverGame::Rtype>(this->port);
        rtype->name = roomName;

		this->roomsMutex.lock();

        rooms.push_back({roomName, this->port, 3});
        
        this->port += 2;
        this->threadPool.push_back(std::thread(rtypeThread, rtype));
		this->roomsMutex.unlock();

        std::cout << "New Room Created :" << roomName << std::endl;
}


void serverGame::ServerRooms::getRooms(boost::asio::ip::udp::endpoint endpoint)
{
		this->roomsMutex.lock();
        ecs::Buffer buffer;
        buffer.writeMessageType(ecs::MessageType::GetRooms);

        for (const auto& room : rooms) {
            buffer.writeString(room.name);
            buffer.writeInt(room.port);
            buffer.writeInt(room.availableSlots);
            server.sendMessage(buffer, endpoint);
        }
		this->roomsMutex.unlock();


}
