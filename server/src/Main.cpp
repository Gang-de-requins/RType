#include <iostream>

#include "Server.hpp"

void receiveMessageThread(std::shared_ptr<server::Server> server)
{
    while (true)
    {
        ecs::Message msg;

        server->receive(msg);
        server->mutex.lock();
        server->messageList.push_back(msg);
        server->mutex.unlock();
    }
}

void sendGameStateThread(std::shared_ptr<server::Server> server) {
    while (true) {
        server->sendGameState();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 32));
    }
}

static int checkArgs(int ac, char const * const *av)
{
    if (ac != 2) {
        std::cerr << "Usage: " << av[0] << " port" << std::endl;
        return EXIT_FAILURE;
    }

    try {
        int port = std::stoi(av[1]);

        if (port < 0 || port > 65535)
            throw std::exception();
    } catch (std::exception &e) {
        std::cerr << "Invalid port" << std::endl;
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

int main(int ac, char const * const *av)
{
    if (checkArgs(ac, av) == EXIT_FAILURE)
        return EXIT_FAILURE;

    srand(time(NULL));
    try {
        std::shared_ptr<server::Server> server = std::make_shared<server::Server>(std::stoi(av[1]));
        std::thread receive(receiveMessageThread, server);
        std::thread send(sendGameStateThread, server);
        server->run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
