#include "../include/fsm.h"
#include <iostream>
#include <chrono>

FSM::FSM() : current_state(State::Idle), session_start_time(0) {}

void FSM::handle_message(const std::string& message) {
    switch (current_state) {
        case State::Idle:
            if (message == "0A0#6601" || message == "0A0#FF01") {
                transition_to(State::Run);
            }
            break;
        case State::Run:
            if (message == "0A0#66FF") {
                transition_to(State::Idle);
            } else {
                log_message(message);
            }
            break;
    }
}

State FSM::get_state() const {
    return current_state;
}

void FSM::transition_to(State new_state) {
    if (current_state == State::Run && new_state == State::Idle) {
        compute_statistics();
        if (log_file.is_open()) {
            log_file.close();
        }
    }
    current_state = new_state;
    if (current_state == State::Run) {
        // Apri un nuovo file di log per la sessione
        auto timestamp = std::chrono::system_clock::now().time_since_epoch().count();
        log_file.open("log_" + std::to_string(timestamp) + ".txt");
        session_start_time = timestamp;
    }
}

void FSM::log_message(const std::string& message) {
    if (log_file.is_open()) {
        auto now = std::chrono::system_clock::now().time_since_epoch().count();
        log_file << now << " " << message << std::endl;
        // Aggiungi il timestamp alla mappa
        uint16_t message_id = std::stoul(message.substr(0, 3), nullptr, 16);
        message_timestamps[message_id].push_back(now);
    }
}

void FSM::compute_statistics() {
    // Calcola e salva le statistiche sui messaggi
    std::ofstream stats_file("stats.csv");
    stats_file << "ID,number_of_messages,mean_time\n";
    for (const auto& entry : message_timestamps) {
        uint16_t id = entry.first;
        const auto& timestamps = entry.second;
        if (timestamps.size() > 1) {
            uint64_t total_time = 0;
            for (size_t i = 1; i < timestamps.size(); ++i) {
                total_time += (timestamps[i] - timestamps[i - 1]);
            }
            double mean_time = static_cast<double>(total_time) / (timestamps.size() - 1);
            stats_file << std::hex << id << "," << std::dec << timestamps.size() << "," << mean_time << "\n";
        } else {
            stats_file << std::hex << id << "," << std::dec << timestamps.size() << ",0\n";
        }
    }
    stats_file.close();
    message_timestamps.clear(); // Resetta i timestamp dei messaggi per la nuova sessione
}
