#include "CallRepository.h"

#include <fstream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

CallRepository::CallRepository() {

    std::ifstream file("call-management-backend/data/calls.json");

    json data;
    file >> data;

    for (int i = 0; i < data.size(); i++)
    {

        Call call;
        call.id = data[i]["id"];
        call.from_number = data[i]["from_number"];
        call.to_number = data[i]["to_number"];
        call.duration = data[i]["duration"];
        call.is_archived = data[i]["is_archived"];
        call.created_at = data[i]["created_at"];

        if (data[i]["direction"] == "Inbound")
        {
            call.direction = Direction::Inbound;
        }
        else
        {
            call.direction = Direction::Outbound;
        }

        if (data[i]["call_type"] == "Answered")
        {
            call.calltype = CallType::Answered;
        }
        else if (data[i]["call_type"] == "Missed")
        {
            call.calltype = CallType::Missed;
        }
        else
        {
            call.calltype = CallType::Voicemail;
        }
        calls.push_back(call);
    }    

    std::ifstream notesFile("call-management-backend/data/notes.json");

    json notesData;
    notesFile >> notesData;

    for (int i = 0; i < notesData.size(); i++)
    {
        Note note;
        note.id = notesData[i]["id"];
        note.call_id = notesData[i]["call_id"];
        note.content = notesData[i]["content"];
        notes.push_back(note);
    }

}

std::vector<Call> CallRepository::getAllCalls(){

    std::vector<Call> activeCalls;

        for (int i = 0; i < calls.size(); i++)
    {
        if (calls[i].is_archived == false)
        {
            activeCalls.push_back(calls[i]);
        }
    }

    return activeCalls;
}


Call* CallRepository::getCallById(int id) {


    
    for (int i = 0; i < calls.size(); i++)
    {
        if (calls[i].id == id)
        {
            calls[i].notes.clear();

            for (int j = 0; j < notes.size(); j++)
            {
                if (notes[j].call_id == id)
                {
                    calls[i].notes.push_back(notes[j]);
                }
            }

            return &calls[i];
        }
    }
    

    return nullptr;
}

Call* CallRepository::archiveCall(int id)
{
    Call* call = getCallById(id);

    if (call == nullptr)
    {
        return nullptr;
    }

    call->is_archived = true;

    return call;
}