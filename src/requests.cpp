#ifndef DEBUG
#include "requests.hpp"
#endif

#include <string>
#include <map>
#include "asio.hpp"

void requests::url_parse::parse(std::string url){
    this->protocol = url.substr(0, url.find("://"));
    if(this->protocol == "http" || this->protocol == "https"){
        this->host = url.substr(url.find("://") + 3, url.find("/", url.find("://") + 3) - url.find("://") - 3);
        this->path = url.substr(url.find("/", url.find("://") + 3), url.size() - url.find("/", url.find("://") + 3));
    } else {
        this->host = url.substr(0, url.find("/"));
        this->path = url.substr(url.find("/"), url.size() - url.find("/"));
        this->protocol = "http";
    }
    this->url = this->protocol + "://" + this->host + "/" + this->path;
}

requests::url_parse::url_parse(const char* curl){
    this->parse(curl);
}

requests::url_parse::url_parse(std::string url){
    this->parse(url);
}

std::string requests::url_parse::get_protocol(){
    return this->protocol;
}

std::string requests::url_parse::get_host(){
    return this->host;
}

std::string requests::url_parse::get_path(){
    return this->path;
}


std::string requests::request(std::string method, requests::url_parse url, requests::header headers, std::string body){
    asio::io_context io_context;
    asio::ip::tcp::resolver resolver(io_context);
    asio::ip::tcp::socket socket(io_context);
    asio::connect(socket, resolver.resolve(url.get_host(), url.get_protocol()));
    std::string request_body = method + " " + url.get_path() + " HTTP/1.1\r\nHost: " + url.get_host() + "\r\n";
    for(auto header : headers){
        request_body += header.first + ": " + header.second + "\r\n";
    }
    if(body != ""){
        request_body += "Content-Length: " + std::to_string(body.size()) + "\r\n";
    }
    request_body += "\r\n";
    if(body != ""){
        request_body += body;
    }
    asio::write(socket, asio::buffer(request_body));
    asio::streambuf response;
    asio::read_until(socket, response, "\r\n");
    return asio::buffer_cast<const char*>(response.data());
}

std::string requests::get(requests::url_parse url, requests::header headers){
    return requests::request("GET", url, headers);
}

std::string requests::post(requests::url_parse url, requests::header headers, std::string body){
    return requests::request("POST", url, headers, body);
}
