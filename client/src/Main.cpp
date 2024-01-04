#include "Game.hpp"

int checkArguments(int ac, char const * const *av);

int main(int ac, char const * const *av)
{
    if (checkArguments(ac, av) == EXIT_FAILURE)
        return 84;

    rtype::Game game(av[1], std::stoi(av[2]));

    game.run();
    return EXIT_SUCCESS;
}
