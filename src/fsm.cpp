// fsm.cpp
#include "./../include/fsm.h"
#include "./../include/message.h"
#include <chrono>
#include <iomanip>
#include <iostream>
#include <filesystem> // Include per le operazioni sul filesystem

namespace fs = std::filesystem;

// Costruttore della classe FSM
FSM::FSM() : current_state(State::Idle), session_start_time(0) {
    // Crea la directory "generatedFiles" se non esiste
    // In questa directory verranno inseriti i file che vengono creati in esecuzione
    fs::create_directories("generatedFiles");
}

// Gestisce il messaggio ricevuto
void FSM::handle_message(const std::string& raw_message) {
    Message message;

    // Tenta di fare il parsing del messaggio iniziale
    if (!MessageParser::parse(raw_message, message)) {
        return; // Se il parsing fallisce esce dalla funzione
    }

    // Timestamp corrente in millisecondi
    uint64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
        std::chrono::system_clock::now().time_since_epoch()).count();

    // Gestisce la FSM in base allo stato attuale
    switch (current_state) {
        case State::Idle:
            // Cambia da Idle a Run
            if (raw_message == "0A0#6601" || raw_message == "0A0#FF01") {
                transition_to(State::Run);
            }
            break;
        case State::Run:
            // Cambia da Run a Idle
            if (raw_message == "0A0#66FF") {
                transition_to(State::Idle);
            } else {
                // Registra il messaggio nel file di log e memorizza il timestamp
                log_message(raw_message);
                message_timestamps[message.id].push_back(current_time);
            }
            break;
    }
}

// Cambia lo stato
void FSM::transition_to(State new_state) {
    // Se sta passando dallo stato Run allo stato Idle
    if (current_state == State::Run && new_state == State::Idle) {
        // Chiude il file di log se è aperto
        if (log_file.is_open()) {
            log_file.close();
        }
        // Calcola le statistiche sui messaggi ricevuti
        compute_statistics();
    }

    // Aggiorna lo stato corrente
    current_state = new_state;

    // Se il nuovo stato è Run, apre un nuovo file di log
    if (current_state == State::Run) {
        // Ottiene il timestamp corrente in millisecondi
        session_start_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();

        // Crea un nome per il file di log basato sul timestamp corrente
        std::string filename = "generatedFiles/session_" + std::to_string(session_start_time) + ".log";
        log_file.open(filename, std::ios::out);
    }
}

// Registra il messaggio nel file di log
void FSM::log_message(const std::string& message) {
    // Se il file di log è aperto
    if (log_file.is_open()) {
        // Ottiene il timestamp corrente in millisecondi
        uint64_t current_time = std::chrono::duration_cast<std::chrono::milliseconds>(
            std::chrono::system_clock::now().time_since_epoch()).count();
            
        // Scrive il timestamp e il messaggio nel file di log
        log_file << current_time << " " << message << std::endl;
    }
}

// Calcola le statistiche sui messaggi ricevuti
void FSM::compute_statistics() {
    // Apre il file delle statistiche in modalità append
    std::ofstream stats_file("generatedFiles/statistics.csv", std::ios::out | std::ios::app);
    stats_file << "ID,number_of_messages,mean_time" << std::endl;

    // Per ogni entry nella mappa dei timestamp dei messaggi
    for (const auto& entry : message_timestamps) {
        uint16_t id = entry.first; // ID del messaggio
        const std::vector<uint64_t>& timestamps = entry.second; // Lista dei timestamp

        if (timestamps.size() > 1) {
            uint64_t total_time = 0;
            for (size_t i = 1; i < timestamps.size(); ++i) {
                total_time += timestamps[i] - timestamps[i - 1]; // Somma dei tempi tra i messaggi
            }
            double mean_time = static_cast<double>(total_time) / (timestamps.size() - 1); // Tempo medio tra i messaggi
            stats_file << std::hex << std::setw(3) << std::setfill('0') << id << ","
                       << std::dec << timestamps.size() << "," << mean_time << std::endl;
        } else {
            stats_file << std::hex << std::setw(3) << std::setfill('0') << id << ","
                       << std::dec << timestamps.size() << ",N/A" << std::endl; // Se c'è solo un messaggio, non calcola il tempo medio
        }
    }

    // Pulisce la mappa dei timestamp
    message_timestamps.clear();
}

// Restituisce lo stato attuale della macchina a stati
State FSM::get_state() const {
    return current_state;
}
