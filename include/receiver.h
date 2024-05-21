// receiver.h
#ifndef RECEIVER_H
#define RECEIVER_H

#include <string>
#include <queue>
#include <mutex>
#include <condition_variable>

// Classe per la ricezione dei messaggi
class Receiver {
public:
    Receiver();
    void start(); // Avvia il ricevitore
    std::string get_message(); // Ottiene un messaggio dalla coda

private:
    std::queue<std::string> message_queue; // Coda dei messaggi
    std::mutex queue_mutex; // Mutex per sincronizzare l'accesso alla coda
    std::condition_variable queue_cv; // Variabile di condizione per la coda
};

#endif // RECEIVER_H
