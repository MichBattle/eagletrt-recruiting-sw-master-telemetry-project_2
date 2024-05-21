// main.cpp
#include "./include/fsm.h"
#include "./include/receiver.h"
#include <iostream>

int main() {
    FSM fsm;
    Receiver receiver;

    receiver.start();

    while (true) {
        std::string message = receiver.get_message();
        fsm.handle_message(message);
    }

    return 0;
}
