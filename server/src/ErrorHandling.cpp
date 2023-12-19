#include <iostream>

void displayUsage()
{
    std::cout << "Usage: ./rtype_server port" << std::endl;
}

int checkPort(char const * const *av)
{
    int port = atoi(av[1]);

    if (port < 1024 || port > 65535) {
        displayUsage();
        return 84;
    }
    return EXIT_SUCCESS;
}

int checkArgs(int ac, char const * const *av)
{
    if (ac != 2) {
        displayUsage();
        return 84;
    }
    if (checkPort(av) == 84)
        return 84;
    return EXIT_SUCCESS;
}
