// main.cpp
#include "./include/fsm.h"
#include "./include/receiver.h"
#include "fake_receiver.h" // Include per open_can e close_can
#include <iostream>
#include <filesystem> // Include per le operazioni sul filesystem

namespace fs = std::filesystem; // Alias per un uso più semplice

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

    // Crea la directory "generatedFiles" se non esiste
    fs::create_directories("generatedFiles");

    FSM fsm;
    Receiver receiver;

    receiver.start();

    // Ciclo principale per ricevere e gestire i messaggi
    while (true) {
        std::string message = receiver.get_message();
        fsm.handle_message(message);
    }

    close_can();
    return 0;
}
