// message.cpp
#include "./../include/message.h"

bool MessageParser::parse(const std::string& raw_message, Message& message) {
    size_t hash_pos = raw_message.find('#');
    if (hash_pos == std::string::npos || hash_pos + 1 >= raw_message.size()) {
        return false;
    }

    std::string id_str = raw_message.substr(0, hash_pos);
    std::string payload_str = raw_message.substr(hash_pos + 1);

    if (id_str.length() > 3 || payload_str.length() % 2 != 0 || payload_str.length() > 16) {
        return false;
    }

    message.id = std::stoul(id_str, nullptr, 16);
    message.payload.clear();

    for (size_t i = 0; i < payload_str.length(); i += 2) {
        std::string byte_str = payload_str.substr(i, 2);
        uint8_t byte = static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
        message.payload.push_back(byte);
    }

    return true;
}
