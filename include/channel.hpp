#ifndef __CHANNEL_CPP__
#define __CHANNEL_CPP__

#include <queue>
#include <map>
#include <string>

#include <mutex>
#include <condition_variable>
#include <memory>


struct chan_message {
    std::mutex lock;
    std::condition_variable cond;
    std::queue<std::string> messages;
    chan_message() {};
};

using channel_map = std::map<std::string, std::shared_ptr<chan_message>>;

class chan {
private:
    static channel_map msg_set;
    std::shared_ptr<chan_message> msg;
public:
    chan(std::string);
    void send(const std::string&);
    std::string receive();
    std::string receive_safe();
};

#endif