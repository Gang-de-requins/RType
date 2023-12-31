#include "Server.hpp"

int checkArguments(int ac, char const * const *av);

int main(int ac, char const * const *av)
{
    if (checkArguments(ac, av) == EXIT_FAILURE)
        return 84;

    rtype::Server server(std::stoi(av[1]));

    return EXIT_SUCCESS;
}
