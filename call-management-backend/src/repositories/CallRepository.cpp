
#include "CallRepository.h"
#include <string>
#include <fstream>
#include <nlohmann/json.hpp>
#include <stdexcept>

using json = nlohmann::json;

Direction parseDirection(const std::string& value)
{
    if (value == "Inbound")
    {
        return Direction::Inbound;
    }
    else if (value == "Outbound")
    {
        return Direction::Outbound;
    }

    throw std::invalid_argument("Invalid call direction: " + value);
}

CallType parseCallType(const std::string& value)
{
    if (value == "Answered")
    {
        return CallType::Answered;
    }
    else if (value == "Missed")
    {
        return CallType::Missed;
    }
    else if (value == "Voicemail")
    {
        return CallType::Voicemail;
    }

    throw std::invalid_argument("Invalid call type: " + value);
}

CallRepository::CallRepository()
{
    std::ifstream file("call-management-backend/data/calls.json");

    if (!file.is_open())
    {
        throw std::runtime_error("Failed to open calls.json");
    }

    json data;
    file >> data;

    for (const auto& item : data)
    {
        Call call;
        call.id = item["id"];
        call.from_number = item["from_number"];
        call.to_number = item["to_number"];
        call.duration = item["duration"];
        call.is_archived = item["is_archived"];
        call.created_at = item["created_at"];

        call.direction = parseDirection(item["direction"].get<std::string>());
        call.calltype = parseCallType(item["call_type"].get<std::string>());
        calls.push_back(call);
    }

    std::ifstream notesFile("call-management-backend/data/notes.json");

    if (!notesFile.is_open())
    {
        throw std::runtime_error("Failed to open notes.json");
    }

    json notesData;
    notesFile >> notesData;

    for (const auto& item : notesData)
    {
        Note note;
        note.id = item["id"];
        note.call_id = item["call_id"];
        note.content = item["content"];

        notes.push_back(note);
    }
}

std::vector<Call> CallRepository::getAllCalls() const
{
    std::vector<Call> activeCalls;

    for (int i = 0; i < calls.size(); i++)
    {
        if (!calls[i].is_archived)
        {
            activeCalls.push_back(calls[i]);
        }
    }

    return activeCalls;
}

std::optional<Call> CallRepository::getCallById(int id) const
{
    for (const auto& call : calls)
    {
        if (call.id == id)
        {
            Call result = call;

            result.notes.clear();

            for (const auto& note : notes)
            {
                if (note.call_id == id)
                {
                    result.notes.push_back(note);
                }
            }

            return result;
        }
    }

    return std::nullopt;
}

std::optional<Call> CallRepository::archiveCall(int id)
{
    for (auto& call : calls)
    {
        if (call.id == id)
        {
            call.is_archived = true;

            return getCallById(id);
        }
    }

    return std::nullopt;
}
