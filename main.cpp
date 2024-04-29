#include <iostream>
#include <string>

#include "requests.hpp"



int main() {
    // curl from the url "http://httpbin.org/get"
    std::cout<< requests::get("httpbin.org/get") << std::endl;
    return 0;
}