#pragma once

#include <string>
#include <vector>
#include "Note.h"

enum class Direction {

    Inbound,
    Outbound

};


enum class CallType {

    Answered,
    Missed,
    Voicemail
};

struct Call {

    int id;
    Direction direction;
    CallType calltype;
    std::string from_number;
    std::string to_number;
    int duration;
    bool is_archived;
    std::string created_at;
    std::vector<Note> notes;
};