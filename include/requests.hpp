#ifndef __REQUESTS_HPP__
#define __REQUESTS_HPP__

#include <string>
#include <map>
#include "asio.hpp"

namespace requests{
    using namespace std;
    using namespace asio;
    using header = map<string, string>;
    class url_parse{
    private:
        string url;
        string protocol;
        string host;
        string path;
        void parse(string);
    public:
        url_parse(const char*);
        url_parse(string);
        string get_protocol();
        string get_host();
        string get_path();
    };
    string request(string, url_parse, header = {}, string = "");
    string get (url_parse, header = {});
    string post(url_parse, header = {}, string = "");
}

#endif