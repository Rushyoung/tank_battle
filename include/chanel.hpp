//
// Created by rushy on 24-5-22.
//

#ifndef TANK_BATTLE_CHANEL_HPP
#define TANK_BATTLE_CHANEL_HPP
#include <string>
#include <mutex>
#include <condition_variable>
#include <memory>
#include <iostream>
#include <map>
#include <queue>

using std::cout;
using std::map;
using std::queue;
using std::string;

struct chan_message {
    std::mutex lock;
    std::condition_variable cond;
    std::queue<string> messages;
    chan_message() { cout << "chan_message created\n"; }
};

using channel_map = map<string, std::shared_ptr<chan_message>>;

class chan {
private:
    static channel_map msg_set;
    std::shared_ptr<chan_message> msg;

public:
    chan(string name) {
        auto it = msg_set.find(name);
        if (it == msg_set.end()) {
            msg = std::make_shared<chan_message>();
            msg_set[name] = msg;
        } else {
            msg = it->second;
        }
    }

    void send(const string& message) {
        std::lock_guard<std::mutex> lock(msg->lock);
        msg->messages.push(message);
        msg->cond.notify_one();
    }

    string receive() {
        std::unique_lock<std::mutex> lock(msg->lock);
        msg->cond.wait(lock, [this] { return !msg->messages.empty(); });
        string message = msg->messages.front();
        msg->messages.pop();
        return message;
    }
};

int main() {
    chan("test").send("Hello");
    cout << chan("test").receive() << "\n";
    return 0;
}

#endif //TANK_BATTLE_CHANEL_HPP
