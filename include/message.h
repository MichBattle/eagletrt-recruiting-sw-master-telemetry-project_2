// message.h
#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <cstdint>
#include <vector>

// Definizione della struttura Message
struct Message {
    uint16_t id; // ID del messaggio
    std::vector<uint8_t> payload; // Payload del messaggio
};

// Classe per il parsing dei messaggi
class MessageParser {
public:
    static bool parse(const std::string& raw_message, Message& message); // Parsing del messaggio iniziale
};

#endif // MESSAGE_H
