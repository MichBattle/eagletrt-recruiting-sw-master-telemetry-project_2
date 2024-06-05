#include "./include/fsm.h"
#include "./include/receiver.h"
#include "fake_receiver.h"
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem; // Alias for the filesystem namespace

int main(int argc, char* argv[]) {
    // Check if the correct number of command-line arguments is provided
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_can_data_file>" << std::endl;
        return 1;
    }

    const char* filepath = argv[1]; // Get the file path from the command-line arguments
    if (open_can(filepath) != 0) {
        std::cerr << "Failed to open CAN data file: " << filepath << std::endl;
        return 1;
    }

    // Create "generatedFiles" directory if it doesn't exist
    fs::create_directories("generatedFiles");

    FSM fsm; 
    Receiver receiver; 

    receiver.start(); // Start the receiver thread

    // Main loop to receive and handle messages
    while (true) {
        std::string message = receiver.get_message(); // Get a message from the receiver
        fsm.handle_message(message); // Handle the message with the FSM
    }

    receiver.stop(); // Stop the receiver thread
    close_can(); // Close the CAN data file
    return 0; 
}
// compile command: g++ -std=c++17 -pthread -o can_fsm src/fsm.cpp src/main.cpp src/message.cpp src/receiver.cpp src/fake_receiver.cpp
