#ifndef DEBUG
#include "channel.hpp"
#endif

#include <map>
#include <queue>
#include <string>

#include <mutex>
#include <condition_variable>
#include <memory>


chan::chan(const std::string& name){
    auto it = msg_set.find(name);
    if (it != msg_set.end()) {
        msg = it->second;
    } else {
        msg = std::make_shared<chan_message>();
        msg_set[name] = msg;
    }
}


void chan::send(const std::string& message) {
    std::lock_guard<std::mutex> lock(msg->lock);
    msg->messages.push(message);
    msg->cond.notify_one();
}


std::string chan::receive() {
    std::lock_guard<std::mutex> lock(msg->lock);
    if (msg->messages.empty()) {
        return "";
    }
    std::string message = msg->messages.front();
    msg->messages.pop();
    return message;
}


std::string chan::receive_safe() {
    std::unique_lock<std::mutex> lock(msg->lock);
    msg->cond.wait(lock, [this]{ return !msg->messages.empty(); });
    std::string message = msg->messages.front();
    msg->messages.pop();
    return message;
}