#include "Server.hpp"

namespace rtype {
    Server::Server(const unsigned short port) :
    c_port(port),
    m_acceptor(m_ioService, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), c_port)),
    m_socket(m_ioService)
    {
        asio::io_context io_context;
        asio::ip::tcp::resolver resolver(io_context);
        asio::ip::tcp::resolver::results_type endpoints = resolver.resolve(asio::ip::host_name(), "");

        for (auto &endpoint : endpoints) {
            std::cout << "Server running on " << endpoint.endpoint().address().to_string() << ":" << this->c_port << std::endl;
        }

        this->startAccept();
        this->m_ioService.run();
    }

    void Server::startAccept()
    {
        std::cout << "Waiting for new client..." << std::endl;

        this->m_acceptor.async_accept(this->m_socket, [this](std::error_code ec) {
            if (!ec) {
                std::cout << "New client connected: " << this->m_socket.remote_endpoint().address().to_string() << std::endl;
                this->handleClients();
            } else {
                std::cerr << "Error: " << ec.message() << std::endl;
            }
            this->startAccept();
        });
    }

    void Server::handleClients()
    {
        std::string message = "Hello from server!";
        std::error_code ec;

        asio::write(this->m_socket, asio::buffer(message), ec);
        if (ec) {
            std::cerr << "Error: " << ec.message() << std::endl;
        }
    }
}
