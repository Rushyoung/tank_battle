#include <iostream>
#include "asio.hpp"

int main() {
    // curl from localhost:8080
    asio::io_context io_context;
    asio::ip::tcp::acceptor acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), 8080));
    asio::ip::tcp::socket socket(io_context);
    acceptor.accept(socket);
    asio::streambuf buffer;
    asio::read_until(socket, buffer, "\r\n");
    std::istream stream(&buffer);
    std::string request;
    std::getline(stream, request);
    std::cout << request << std::endl;
}