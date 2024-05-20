// message.h
#ifndef MESSAGE_H
#define MESSAGE_H

#include <sstream>

struct Message {
    uint16_t id;
    std::vector<uint8_t> payload;
};

class MessageParser {
public:

private:
};

#endif // MESSAGE_H
