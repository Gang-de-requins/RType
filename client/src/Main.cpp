#include "Game.hpp"

int checkArguments(int ac, char const * const *av);

int main(int ac, char const * const *av)
{
    if (checkArguments(ac, av) == EXIT_FAILURE)
        return 84;

    rtype::Game game(std::string(av[1]), static_cast<unsigned short>(std::stoul(av[2])), std::string(av[3]));

    game.run();
    return EXIT_SUCCESS;
}
