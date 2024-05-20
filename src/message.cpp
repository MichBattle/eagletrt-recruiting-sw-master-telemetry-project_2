// message.cpp
#include "message.h"

bool MessageParser::parse(const std::string& raw_message) {
    // Trova la posizione di # nel 
    size_t hash_pos = raw_message.find('#');
    // Se non c'è un carattere '#' o se non ci sono caratteri dopo '#', il messaggio non è valido
    if (hash_pos == std::string::npos || hash_pos + 1 >= raw_message.size()) {
        return false;
    }

    return true;
}
