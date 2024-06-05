# Project 2

## Overview

This project implements a CAN Bus message processor in C++. It includes functionalities for state management, message logging, parsing, statistics collection, and multithreaded message reception. The system can transition between two states (`Idle` and `Run`) based on specific CAN messages.

## Components

### 1. FSM State Management:
   - Transitions between `Idle` and `Run` states based on specific CAN messages.
   - Logs received messages with timestamps.
   - Computes and writes statistics to a CSV file upon transitioning to `Idle`.

### 2. Message Parsing:
   - Parses incoming CAN messages into IDs and payloads.
   - Validates payload lengths and converts hexadecimal strings to integers and byte representations.

### 3. Receiver Thread Management:
   - Manages the reception of CAN messages in a separate thread.
   - Starts and stops the receiver thread cleanly.
   - Ensures thread-safe message queue handling.

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
