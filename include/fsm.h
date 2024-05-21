// fsm.h
#ifndef FSM_H
#define FSM_H

#include <string>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <cstdint>

// Definizione degli stati della macchina
enum class State {
    Idle, // Stato idle
    Run   // Stato di esecuzione
};

// Definizione della classe FSM (Finite State Machine)
class FSM {
public:
    FSM();
    void handle_message(const std::string& message); // Gestisce il messaggio ricevuto
    State get_state() const; // Restituisce lo stato attuale della macchina a stati

private:
    void transition_to(State new_state); // Transizione verso un nuovo stato
    void log_message(const std::string& message); // Registra il messaggio nel file di log
    void compute_statistics(); // Calcola le statistiche dei messaggi ricevuti

    State current_state; // Stato attuale della macchina
    std::ofstream log_file; // File di log per i messaggi
    std::unordered_map<uint16_t, std::vector<uint64_t>> message_timestamps; // Timestamp dei messaggi per ID
    uint64_t session_start_time; // Timestamp di inizio sessione
};

#endif // FSM_H
