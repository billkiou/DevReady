
#pragma once

#include <vector>
#include <optional>
#include "../models/Call.h"
#include "../models/Note.h"

class CallRepository {
    public:
        CallRepository();
        std::vector<Call> getAllCalls() const;
        std::optional<Call> getCallById(int id) const;
        std::optional<Call> archiveCall(int id);

    private:
        std::vector<Call> calls;
        std::vector<Note> notes;
};
