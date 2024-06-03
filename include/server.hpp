#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <asio.hpp>
#include <map>
#include <string>

namespace server{
    static const std::string __SERVER__ = "Server: asio/1.0\r\n";
    using header = std::map<std::string, std::string>;
    
    class response{
    private:
        int code;
        header headers;
        std::string message;
    public:
        response(int);
        void add_message(std::string);
        void add_header(std::string, std::string);
        std::string operator()();
    };

    struct receipt{
        std::string method;
        std::string path;
        std::string version;
        header headers;
        std::string body;
    };

    class listener{
    private:
        asio::io_context io_context;
        asio::ip::tcp::acceptor acceptor;
        response (*callback)(receipt);
        int port;
        void do_accept();
    public:
        listener(int, response(*)(receipt));
        ~listener();
        void start_accept();
    };
};

#endif
