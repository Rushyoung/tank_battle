#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <asio.hpp>
#include <map>
#include <string>

namespace server{
    static const std::string __SERVER__ = "Server: asio/1.0\r\n";
    using header = std::map<std::string, std::string>;
    class listener{
    private:
        asio::io_context io_context;
        asio::ip::tcp::acceptor acceptor;
        response (*callback)(std::string);
        int port;
    public:
        listener(int, response(*)(std::string));
        void start_accept();
    };
    
    class response{
    private:
        int code;
        header headers;
        std::string message;
    public:
        response(int);
        void set_message(std::string);
        void add_header(std::string, std::string);
        std::string operator()();
    };
};

#endif
