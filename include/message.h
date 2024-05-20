// message.h
#ifndef MESSAGE_H
#define MESSAGE_H

#include <sstream>
#include <string>
#include <cstdint>
#include <vector>
#include <sstream>
#include <iomanip>


struct Message {
    uint16_t id;
    std::vector<uint8_t> payload;
};

class MessageParser {
public:
    static bool parse(const std::string& raw_message, Message& message);
};

#endif // MESSAGE_H
