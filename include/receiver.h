// receiver.h
#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

class Receiver {
public:
    Receiver();
    void start();
    std::string get_message();

private:
    std::queue<std::string> message_queue;
    std::mutex queue_mutex;
    std::condition_variable queue_cv;
};

#endif // RECEIVER_H
