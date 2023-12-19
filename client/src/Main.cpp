// #include "Game.hpp"

// int main(void)
// {
//     rtype::Game game;

//     game.run();
//     return EXIT_SUCCESS;
// }

#include <iostream>
#include <boost/asio.hpp>
#include "Game.hpp"

int main(int argc, char const * const *argv)
    // try {
    //     boost::asio::io_context io_context;
    //     std::string serverAddress = "127.0.0.1"; // Replace with the server's IP address
    //     unsigned short serverPort = 12345;       // Replace with the server's port number

    //     UDPClient client(io_context, serverAddress, serverPort);
    //     client.start();

    //     io_context.run();
    // } catch (const std::exception &e) {
    //     std::cerr << "Exception: " << e.what() << std::endl;
    // }

{
    if (argc != 4) {
        std::cerr << "Usage: ./rtype_client <host> <port> <name>" << std::endl;
        return 84;
    }

    try {
        std::stoi(argv[2]);
    } catch (const std::exception &e) {
        std::cerr << "Invalid port" << std::endl;
        return 84;
    }

    rtype_client::Game game(argv[1], std::stoi(argv[2]), argv[3]);

    game.run();

    return EXIT_SUCCESS;
}
