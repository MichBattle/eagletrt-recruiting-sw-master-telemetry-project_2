// receiver.cpp
#include "receiver.h"
#include "fake_receiver.h" // Assuming this is provided for CAN reception
#include <thread>
#include <queue>
#include <mutex>
#include <condition_variable>

Receiver::Receiver() {
    // Constructor
}

void Receiver::start() {
    std::thread([this]() {
        while (true) {
            std::string message = can_receive();
            {
                std::lock_guard<std::mutex> lock(queue_mutex);
                message_queue.push(message);
            }
            queue_cv.notify_one();
        }
    }).detach();
}

std::string Receiver::get_message() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    queue_cv.wait(lock, [this]() { return !message_queue.empty(); });
    std::string message = message_queue.front();
    message_queue.pop();
    return message;
}
