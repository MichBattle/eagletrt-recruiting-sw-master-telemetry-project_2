#include "./../include/receiver.h"
#include "../fake_receiver.h"
#include <thread>
#include <cstring>

Receiver::Receiver() : running(false) {
}

Receiver::~Receiver() {
    stop();
}

// Start the receiver
void Receiver::start() {
    running = true;
    // Create a separate thread to receive messages
    receiver_thread = std::thread([this]() {
        while (running) {
            // Buffer for received message
            char message_buffer[MAX_CAN_MESSAGE_SIZE] = {0};
            // Receive a message and get the number of bytes received
            int bytes_received = can_receive(message_buffer);
            if (bytes_received > 0) { // Ensure message is received correctly
                {
                    // Block to protect access to queue
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    // Add received message to queue
                    message_queue.push(std::string(message_buffer, bytes_received));
                }
                // Notify a waiting thread that a new message is available
                queue_cv.notify_one();
            }
        }
    });
}

// Get a message from the queue
std::string Receiver::get_message() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    // Wait until the queue contains at least one message
    queue_cv.wait(lock, [this]() { return !message_queue.empty(); });
    // Get the message from the queue
    std::string message = message_queue.front();
    // Remove the message from the queue
    message_queue.pop();
    return message; 
}

// Stop the receiver and join the thread
void Receiver::stop() {
    if (running) {
        running = false;
        if (receiver_thread.joinable()) {
            receiver_thread.join();
        }
    }
}
