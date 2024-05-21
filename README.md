# Project 2

## Overview

This project implements a CAN Bus message processor in C++. It includes functionalities for state management, message logging, parsing, statistics collection, and multithreaded message reception. The system can transition between two states (`Idle` and `Run`) based on specific CAN messages.

## Components

### 1. FSM (Finite State Machine)

Manages the system states (`Idle` and `Run`).

- **Functions**:
  - `FSM()`
  - `void handle_message(const std::string& message)`
  - `State get_state() const`

- **Private Methods**:
  - `void transition_to(State new_state)`
  - `void log_message(const std::string& message)`
  - `void compute_statistics()`

- **Private Members**:
  - `State current_state`
  - `std::ofstream log_file`
  - `std::unordered_map<uint16_t, std::vector<uint64_t>> message_timestamps`
  - `uint64_t session_start_time`

### 2. Message Parsing

Parses incoming CAN messages into IDs and payloads.

- **Functions**:
  - `static bool parse(const std::string& raw_message, Message& message)`

- **Structure**:
  - `struct Message`

### 3. Thread Receiver

Manages the reception of CAN messages in a separate thread.

- **Functions**:
  - `Receiver()`
  - `void start()`
  - `std::string get_message()`

- **Private Members**:
  - `std::queue<std::string> message_queue`
  - `std::mutex queue_mutex`
  - `std::condition_variable queue_cv`

### 4. Main Application

Controls the overall flow of the application.

- **Main Functions**:
  - Initializes the CAN interface.
  - Starts the receiver and FSM.
  - Handles the continuous loop to process messages.

## Installation

1. **Clone the repository**:
    ```bash
    git clone https://github.com/MichBattle/eagletrt-recruiting-sw-master-telemetry-project_2.git
    ```

2. **Build the project**:
    ```bash
    mkdir -p build
    cd build
    cmake ..
    make -j$(sysctl -n hw.logicalcpu)
    ```

## Usage

1. **Run the main application**:
    ```bash
    ./bin/project_2 path/to/can_data_file
    ```

2. **Simulate CAN messages**:
    - Open `candump.log` file and append CAN messages to simulate.

## File Descriptions

- `include/fsm.h`: Header for state management.
- `include/message.h`: Header for message parsing.
- `include/receiver.h`: Header for the message receiver.
- `src/fsm.cpp`: Implementation of the FSM.
- `src/message.cpp`: Implementation of message parsing.
- `src/receiver.cpp`: Implementation of the message receiver.
- `main.cpp`: Main application logic.

## Files structure
```
├── .vscode
│   └── settings.json
├── CMakeLists.txt
├── bin
│   └── project_2
├── build
├── candump.log
├── fake_receiver.cpp
├── fake_receiver.h
├── generatedFiles
├── include
│   ├── fsm.h
│   ├── message.h
│   └── receiver.h
├── main.cpp
├── src
│   ├── fsm.cpp
│   ├── message.cpp
│   └── receiver.cpp
└── telemetry
```

## Acknowledgments

- Assignment for E-Agle Trento Racing Team Recruitment
