#include <iostream>
#include <string>

#include <thread>

#include "requests.hpp"
#include "server.hpp"

using namespace std;

string hello(string message){
    cout << "Received: " << message << endl;
    return "Hello, world!";
}

int main() {
    // curl from the url "http://httpbin.org/get"
    server::listener listener(8080, hello);
    listener.start_accept();
    server::string url = "http://httpbin.org/get";
}