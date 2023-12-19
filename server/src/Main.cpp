#include "Server.hpp"

int checkArgs(int ac, char const * const *av);

int main(int ac, char const * const *av)
{
    if (checkArgs(ac, av) == 84)
        return 84;
    rtype::Server server(std::stoi(av[1]));

    server.run();
    return EXIT_SUCCESS;
}
