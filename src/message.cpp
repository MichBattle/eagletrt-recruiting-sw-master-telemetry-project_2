#include "./../include/message.h"
#include <sstream>
#include <iomanip>

// Parsing the initial message
bool MessageParser::parse(const std::string& raw_message, Message& message) {
    // Find the position of the '#' character in the raw message
    size_t hash_pos = raw_message.find('#');
    if (hash_pos == std::string::npos || hash_pos + 1 >= raw_message.size()) {
        return false; // Return false if '#' is not found or it's the last character
    }

    // Extract the parts of the message before and after the '#'
    std::string id_str = raw_message.substr(0, hash_pos);
    std::string payload_str = raw_message.substr(hash_pos + 1);

    // Validate lengths of ID and payload
    if (id_str.length() > 3 || payload_str.length() % 2 != 0 || payload_str.length() > 16) {
        return false; // Return false if data is invalid
    }

    // Convert ID from hex string to integer
    try {
        message.id = std::stoul(id_str, nullptr, 16);
    } catch (const std::invalid_argument& e) {
        return false; // Return false if the conversion fails
    }

    message.payload.clear();

    // Convert payload from hex string to byte vector
    for (size_t i = 0; i < payload_str.length(); i += 2) {
        std::string byte_str = payload_str.substr(i, 2);
        try {
            uint8_t byte = static_cast<uint8_t>(std::stoul(byte_str, nullptr, 16));
            message.payload.push_back(byte);
        } catch (const std::invalid_argument& e) {
            return false; 
        }
    }

    return true; 
}
