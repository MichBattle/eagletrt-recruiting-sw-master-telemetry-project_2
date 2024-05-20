// fsm.h
#ifndef FSM_H
#define FSM_H

enum class State {
    Idle,
    Run
};

class FSM {
public:
    FSM();
    void handle_message(const std::string& message);
    State get_state() const;

private:
    void transition_to(State new_state);
    void log_message(const std::string& message);
    void compute_statistics();

    State current_state;
    std::ofstream log_file;
    std::unordered_map<uint16_t, std::vector<uint64_t>> message_timestamps;
    uint64_t session_start_time;
};

#endif // FSM_H
