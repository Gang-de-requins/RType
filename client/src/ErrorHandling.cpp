#include <iostream>
#include <string>

static int checkPort(char const * const *av)
{
    try {
        int port = std::stoi(av[2]);

        if (port < 0 || port > 65535)
            throw std::invalid_argument("Port must be between 0 and 65535");
    } catch (std::invalid_argument const &e) {
        std::cerr << "Invalid port: " << e.what() << std::endl;
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}

int checkArguments(int ac, char const * const *av)
{
    if (ac != 4) {
        std::cerr << "Usage: ./rtype_server <ip> <port> <playerName>" << std::endl;
        return EXIT_FAILURE;
    }

    if (checkPort(av) == EXIT_FAILURE)
        return EXIT_FAILURE;

    return EXIT_SUCCESS;
}
