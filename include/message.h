#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <vector>
#include <cstdint>

// Message structure
struct Message {
    uint16_t id; // ID represented as a 16-bit unsigned integer
    std::vector<uint8_t> payload; // Payload represented as a vector of bytes
};

// Message parser class
class MessageParser {
public:
    static bool parse(const std::string& raw_message, Message& message); // Parses the raw message into a Message struct
};

#endif // MESSAGE_H
