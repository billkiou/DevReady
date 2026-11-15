
#include <iostream>
#include <vector>
#include "../src/repositories/CallRepository.h"

int main()
{
    std::cout << "Call Management Backend" << std::endl;

    // Create repository and load calls and notes from JSON files
    CallRepository repository;

    // Search for a call that does not exist
    auto missingCall = repository.getCallById(999);

    if (!missingCall.has_value())
    {
        std::cout << "Call 999 not found" << std::endl;
    }

    // Get a call that exists but has no notes
    auto call11 = repository.getCallById(11);

    if (call11.has_value())
    {
        std::cout << "Call 11 notes: " << call11->notes.size() << std::endl;
    }

    // Get an existing call and check its notes
    auto call = repository.getCallById(1);

    if (call.has_value())
    {
        std::cout << "Call found! ID: " << call->id << std::endl;
        std::cout << "Notes count: " << call->notes.size() << std::endl;
    }
    else
    {
        std::cout << "Call not found!" << std::endl;
    }

    // Archive an existing call
    auto archived = repository.archiveCall(1);

    if (archived.has_value())
    {
        std::cout << "Call archived successfully!" << std::endl;
        std::cout << "Is archived: " << archived->is_archived << std::endl;
    }
    else
    {
        std::cout << "Call not found!" << std::endl;
    }

    // Try to archive a call that does not exist
    auto missingArchive = repository.archiveCall(999);

    if (!missingArchive.has_value())
    {
        std::cout << "Call 999 cannot be archived" << std::endl;
    }

    // Get all non-archived calls
    std::vector<Call> activeCalls = repository.getAllCalls();

    std::cout << "Active Calls:" << std::endl;

    for (const auto& activeCall : activeCalls)
    {
        std::cout << "Call ID: " << activeCall.id << std::endl;
    }

    return 0;
}
