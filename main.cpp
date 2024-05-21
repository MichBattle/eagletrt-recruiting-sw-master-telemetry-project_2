// main.cpp
#include "./include/fsm.h"
#include "./include/receiver.h"
#include "fake_receiver.h" // Include this for open_can and close_can
#include <iostream>
#include <filesystem> // Include for filesystem operations

namespace fs = std::filesystem; // Alias for easier use

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <path_to_can_data_file>" << std::endl;
        return 1;
    }

    const char* filepath = argv[1];
    if (open_can(filepath) != 0) {
        std::cerr << "Failed to open CAN data file: " << filepath << std::endl;
        return 1;
    }

    // Create the directory if it doesn't exist
    fs::create_directories("generatedFiles");

    FSM fsm;
    Receiver receiver;

    receiver.start();

    while (true) {
        std::string message = receiver.get_message();
        fsm.handle_message(message);
    }

    close_can();
    return 0;
}
