#include "./../include/fsm.h"
#include "./../include/message.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <filesystem>
#include <fstream>

namespace fs = std::filesystem; // Alias for the filesystem namespace

// Constructor for FSM class
FSM::FSM() : current_state(State::Idle), session_start_time(0) {
    // Create "generatedFiles" directory if it doesn't exist
    fs::create_directories("generatedFiles");
}

// Handle received message
void FSM::handle_message(const std::string& raw_message) {
    Message message;

    // Attempt to parse the initial message
    if (!MessageParser::parse(raw_message, message)) {
        return; 
    }

    // Current timestamp in milliseconds
    uint64_t current_time = get_current_time_ms();

    // Handle FSM based on current state
    switch (current_state) {
        case State::Idle:
            // Transition from Idle to Run
            if (message.id == 0x0A0 && (message.payload == std::vector<uint8_t>{0x66, 0x01} || 
                                        message.payload == std::vector<uint8_t>{0xFF, 0x01})) {
                transition_to(State::Run);
            }
            break;
        case State::Run:
            // Transition from Run to Idle
            if (message.id == 0x0A0 && message.payload == std::vector<uint8_t>{0x66, 0xFF}) {
                transition_to(State::Idle);
            } else {
                // Log message and store timestamp
                log_message(raw_message);
                message_timestamps[message.id].push_back(current_time);
            }
            break;
    }
}

// Transition to new state
void FSM::transition_to(State new_state) {
    // Transition from Run to Idle
    if (current_state == State::Run && new_state == State::Idle) {
        // Close log file if open
        if (log_file.is_open()) {
            log_file.close();
        }
        // Compute statistics on received messages
        compute_statistics();
    }

    // Update current state
    current_state = new_state;

    // Open new log file if transitioning to Run state
    if (current_state == State::Run) {
        session_start_time = get_current_time_ms();

        // Create a filename for the log file based on the current timestamp
        std::string filename = "generatedFiles/session_" + std::to_string(session_start_time) + ".log";
        log_file.open(filename, std::ios::out);
    }
}

// Log message to file
void FSM::log_message(const std::string& message) {
    // If log file is open
    if (log_file.is_open()) {
        uint64_t current_time = get_current_time_ms();
            
        // Write timestamp and message to log file
        log_file << current_time << " " << message << std::endl;
    }
}

// Compute statistics on received messages
void FSM::compute_statistics() {
    // Open statistics file in append mode
    std::ofstream stats_file("generatedFiles/statistics.csv", std::ios::out | std::ios::app);
    stats_file << "ID,number_of_messages,mean_time" << std::endl;

    // For each entry in the message timestamp map
    for (const auto& entry : message_timestamps) {
        uint16_t id = entry.first; // Message ID
        const std::vector<uint64_t>& timestamps = entry.second; // List of timestamps

        if (timestamps.size() > 1) {
            uint64_t total_time = 0;
            for (size_t i = 1; i < timestamps.size(); ++i) {
                total_time += timestamps[i] - timestamps[i - 1]; // Sum of times between messages
            }
            double mean_time = static_cast<double>(total_time) / (timestamps.size() - 1); // Mean time between messages
            stats_file << std::hex << std::setw(3) << std::setfill('0') << id << ","
                       << std::dec << timestamps.size() << "," << mean_time << std::endl;
        } else {
            stats_file << std::hex << std::setw(3) << std::setfill('0') << id << ","
                       << std::dec << timestamps.size() << ",N/A" << std::endl; // If only one message, no mean time calculation
        }
    }

    // Clear message timestamp map
    message_timestamps.clear();
}

// Return current state of the state machine
State FSM::get_state() const {
    return current_state;
}

// Get the current timestamp in milliseconds
uint64_t FSM::get_current_time_ms() const {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
}
