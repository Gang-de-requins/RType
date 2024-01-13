/*
** EPITECH PROJECT, 2023
** r type
** File description:
** Server
*/

#include "../include/ServerRooms.hpp"
#include "Rtype.hpp"

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
    if (checkArgs(ac, av) == EXIT_FAILURE)
        return EXIT_FAILURE;

    srand(static_cast<unsigned int>(time(NULL)));
    try {
        std::shared_ptr<server::Server> server = std::make_shared<server::Server>(std::stoi(av[1]));
        std::thread receive(receiveMessageThread, server);

        server->run();
    }
    catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    return EXIT_SUCCESS;
}
