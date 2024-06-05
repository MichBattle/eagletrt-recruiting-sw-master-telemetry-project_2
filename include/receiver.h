#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>
#include <thread>

class Receiver {
public:
    Receiver(); 
    ~Receiver(); 
    void start(); // Method to start the receiver thread
    std::string get_message(); // Method to get a message from the queue
    void stop(); // Method to stop the receiver thread

private:
    std::queue<std::string> message_queue; // Queue to hold received messages
    std::mutex queue_mutex; // Mutex to protect access to the queue
    std::condition_variable queue_cv; // Condition variable for message availability
    std::thread receiver_thread; // Thread for receiving messages
    bool running; // Flag to control the running state of the receiver thread
};

#endif // RECEIVER_H
