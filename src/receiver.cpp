// receiver.cpp
#include "./../include/receiver.h"
#include "../fake_receiver.h"
#include <thread>
#include <cstring>

Receiver::Receiver() {
    // Constructor
}

void Receiver::start() {
    std::thread([this]() {
        while (true) {
            char message_buffer[MAX_CAN_MESSAGE_SIZE] = {0};
            int bytes_received = can_receive(message_buffer);
            if (bytes_received > 0) { // Ensure message is received successfully
                {
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    message_queue.push(std::string(message_buffer, bytes_received));
                }
                queue_cv.notify_one();
            }
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
