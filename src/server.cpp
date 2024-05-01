#ifndef DEBUG
#include "server.hpp"
#endif

#include <asio.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

server::listener::listener(int port, std::string(*func)(std::string)): acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)){
    this->callback = func;
    this->port = port;
}

void server::listener::start_accept(){
    // Keep listening for the port
    // When a connection is made, call the callback function
    // the callback function should return a string
    // send the string to the client
    // close the connection
    // repeat
    std::cout << "Listening on port " << this->port << std::endl;
    while(true){
        asio::ip::tcp::socket socket(io_context);
        acceptor.accept(socket);
        asio::streambuf buffer;
        asio::read_until(socket, buffer, "\n");
        std::istream is(&buffer);
        std::string message;
        std::getline(is, message);
        message = this->callback(message);
        asio::write(socket, asio::buffer(message));
        socket.close();
        std::this_thread::sleep_for(std::chrono::milliseconds(1)); 
    }
}

server::response::response(int code){
    this->code = code;
}

void server::response::set_message(std::string message){
    this->message = message;
}

void server::response::add_header(std::string key, std::string value){
    this->headers[key] = value;
}

std::string server::response::operator()(){
    std::string response = "HTTP/1.1 " + std::to_string(this->code) + " OK\r\n";
    for(auto it = this->headers.begin(); it != this->headers.end(); it++){
        response += it->first + ": " + it->second + "\r\n";
    }
    response += "\r\n" + this->message;
    return response;
}