// message.cpp
#include "message.h"

bool MessageParser::parse(const std::string& raw_message) {
    // Trova la posizione di # nel 
    size_t hash_pos = raw_message.find('#');
    // Se non c'è un carattere '#' o se non ci sono caratteri dopo '#', il messaggio non è valido
    if (hash_pos == std::string::npos || hash_pos + 1 >= raw_message.size()) {
        return false;
    }

    std::string id_str = raw_message.substr(0, hash_pos); // Estraggo la stringa fino al #
    std::string payload_str = raw_message.substr(hash_pos + 1);// Estraggo la stringa dopo il #

    //controllo lunghezza stringhe ottenute
    if (id_str.length() > 3 || payload_str.length() % 2 != 0 || payload_str.length() > 16) {
        return false;
    }

    message.id = std::stoul(id_str, nullptr, 16); // converto prima parte del messaggio da esadecimale a intero
    message.payload.clear(); // svuoto payload di prima

    //completo il payload
    for (size_t i = 0; i < payload_str.length(); i += 2) {
        std::string byte_str = payload_str.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
        message.payload.push_back(byte);
    }

    return true;
}
