// message.cpp
#include "./../include/message.h"

// Parsing del messaggio iniziale
bool MessageParser::parse(const std::string& raw_message, Message& message) {
    // Trova la posizione del carattere '#' nel messaggio grezzo
    size_t hash_pos = raw_message.find('#');
    if (hash_pos == std::string::npos || hash_pos + 1 >= raw_message.size()) {
        return false; // Ritorna false se non trova '#' o se è l'ultimo carattere
    }

    // Estrae la parte del messaggio prima e dopo il carattere '#'
    std::string id_str = raw_message.substr(0, hash_pos);
    std::string payload_str = raw_message.substr(hash_pos + 1);

    // Controlla che la lunghezza dell'ID e del payload sia valida
    if (id_str.length() > 3 || payload_str.length() % 2 != 0 || payload_str.length() > 16) {
        return false; // Ritorna false se i dati non sono validi
    }

    // Converte l'ID da stringa esadecimale a intero
    message.id = std::stoul(id_str, nullptr, 16);
    message.payload.clear();

    // Converte il payload da stringa esadecimale a vettore di byte
    for (size_t i = 0; i < payload_str.length(); i += 2) {
        std::string byte_str = payload_str.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
        message.payload.push_back(byte);
    }

    return true; // Ritorna true se il parsing ha successo
}
