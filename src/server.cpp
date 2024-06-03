#ifndef DEBUG
#include "server.hpp"
#endif

#include <asio.hpp>

#include <iostream>
#include <string>
#include <thread>
#include <chrono>

/* ========= listener ========= */
server::listener::listener(int port, response(*func)(server::receipt))
    :  port(port), callback(callback), acceptor(io_context, asio::ip::tcp::endpoint(asio::ip::tcp::v4(), port)) {
}

server::listener::~listener(){
    io_context.stop();
    acceptor.close();
}

void server::listener::start_accept(){
    std::cout << "Listening on port " << this->port << std::endl;
    // start do_accept in a new thread
    do_accept();
    io_context.run();
}

void server::listener::do_accept(){
    acceptor.async_accept([this](std::error_code ec, asio::ip::tcp::socket socket) {
        if (!ec) {
            std::string data;
            asio::read(socket, asio::buffer(data));
            server::receipt receipt{data};
            server::response response = callback(receipt);
            asio::write(socket, asio::buffer(response()));
        }
        do_accept();
    });
}


/* ========= response ========= */
server::response::response(int code){
    this->code = code;
}

void server::response::add_message(std::string message){
    this->message += message;
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