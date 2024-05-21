// receiver.cpp
#include "./../include/receiver.h"
#include "../fake_receiver.h"
#include <thread>
#include <cstring>

// Costruttore della classe Receiver
Receiver::Receiver() {
    // Costruttore vuoto
}

// Avvia il ricevitore
void Receiver::start() {
    // Crea un thread separato per ricevere i messaggi
    std::thread([this]() {
        while (true) {
            // Buffer per il messaggio ricevuto
            char message_buffer[MAX_CAN_MESSAGE_SIZE] = {0};
            // Riceve un messaggio e ottiene il numero di byte ricevuti
            int bytes_received = can_receive(message_buffer);
            if (bytes_received > 0) { // Assicura che il messaggio sia ricevuto correttamente
                {
                    // Blocco per proteggere l'accesso alla coda
                    std::lock_guard<std::mutex> lock(queue_mutex);
                    // Aggiunge il messaggio ricevuto alla coda
                    message_queue.push(std::string(message_buffer, bytes_received));
                }
                // Notifica un thread in attesa che un nuovo messaggio è disponibile
                queue_cv.notify_one();
            }
        }
    }).detach(); // Stacca il thread
}

// Ottiene un messaggio dalla coda
std::string Receiver::get_message() {
    std::unique_lock<std::mutex> lock(queue_mutex);
    // Attende finché la coda non contiene almeno un messaggio
    queue_cv.wait(lock, [this]() { return !message_queue.empty(); });
    // Ottiene il messaggio dalla coda
    std::string message = message_queue.front();
    // Rimuove il messaggio dalla coda
    message_queue.pop();
    return message; // Ritorna il messaggio
}
