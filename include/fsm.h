#ifndef FSM_H
#define FSM_H

#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cstdint>

// Definition of the states of the machine
enum class State {
    Idle, 
    Run 
};

// Definition of the FSM (Finite State Machine) class
class FSM {
public:
    FSM();
    void handle_message(const std::string& message); // Handles the received message
    State get_state() const; // Returns the current state of the state machine

private:
    void transition_to(State new_state); // Transition to a new state
    void log_message(const std::string& message); // Logs the message to the log file
    void compute_statistics(); // Computes statistics of the received messages

    State current_state; // Current state of the machine
    std::ofstream log_file; // Log file for the messages
    std::unordered_map<uint16_t, std::vector<uint64_t>> message_timestamps; // Message timestamps by ID
    uint64_t session_start_time; // Session start timestamp
    uint64_t get_current_time_ms() const; // Returns the current timestamp in milliseconds
};

#endif // FSM_H
