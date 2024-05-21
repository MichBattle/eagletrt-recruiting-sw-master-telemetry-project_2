// fsm.cpp
#include "fsm.h"
#include "message.h"
#include <chrono>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <vector>
#include <iomanip>

FSM::FSM() : current_state(State::Idle), session_start_time(0) {}

void FSM::handle_message(const std::string& raw_message) {
}

void FSM::transition_to(State new_state) {
    if (current_state == State::Run && new_state == State::Idle) {
        if (log_file.is_open()) {
            log_file.close();
        }
        compute_statistics();
    }

    current_state = new_state;

    if (current_state == State::Run) {
        session_start_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

        std::string filename = "session_" + std::to_string(session_start_time) + ".log";
        log_file.open(filename, std::ios::out);
    }
}

void FSM::log_message(const std::string& message) {
    if (log_file.is_open()) {
        uint64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

        log_file << current_time << " " << message << std::endl;
    }
}

void FSM::compute_statistics() {
    std::ofstream stats_file("statistics.csv", std::ios::out | std::ios::app);
    stats_file << "ID,number_of_messages,mean_time" << std::endl;

    for (const auto& entry : message_timestamps) {
        uint16_t id = entry.first;
        const std::vector<uint64_t>& timestamps = entry.second;

        if (timestamps.size() > 1) {
            uint64_t total_time = 0;
            for (size_t i = 1; i < timestamps.size(); ++i) {
                total_time += timestamps[i] - timestamps[i - 1];
            }
            double mean_time = static_cast<double>(total_time) / (timestamps.size() - 1);
            stats_file << std::hex << std::setw(3) << std::setfill('0') << id << ","
                       << std::dec << timestamps.size() << "," << mean_time << std::endl;
        } else {
            stats_file << std::hex << std::setw(3) << std::setfill('0') << id << ","
                       << std::dec << timestamps.size() << ",N/A" << std::endl;
        }
    }

    message_timestamps.clear();
}

State FSM::get_state() const {
    return current_state;
}
