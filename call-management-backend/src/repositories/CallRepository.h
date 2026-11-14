#pragma once

#include <vector>
#include "../models/Call.h"
#include "../models/Note.h"

class CallRepository {
    public:
        CallRepository();
        std::vector<Call> getAllCalls();
        Call* getCallById(int id);
        Call* archiveCall(int id);
    private:
        std::vector<Call> calls;
        std::vector<Note> notes;
};