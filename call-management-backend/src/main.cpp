#include <iostream>
#include <crow.h>
#include "repositories/CallRepository.h"
#include <stdexcept>

int main()
{
    crow::SimpleApp app;

    app.exception_handler([](crow::response& res) {

        res.code = 500;
        res.set_header("Content-Type", "application/json");
        res.body = R"({"error":"Internal server error"})";
        res.end();
    });


    CallRepository repository;

    CROW_ROUTE(app, "/calls") ([&repository]() {

        std::vector<Call> calls = repository.getAllCalls();
        std::cout << "Number of calls: " << calls.size() << std::endl;
        crow::json::wvalue response;
        response["calls"] = crow::json::wvalue::list();

        for (size_t i = 0; i <calls.size(); i++)
        {
            crow::json::wvalue callJson;

            callJson["id"] = calls[i].id;
            callJson["direction"] = (calls[i].direction == Direction::Inbound) ? "inbound" : "outbound";
            callJson["call_type"] = (calls[i].calltype == CallType::Answered) ? "answered" : (calls[i].calltype == CallType::Missed) ? "missed" : "voicemail";
            callJson["from_number"] = calls[i].from_number;
            callJson["to_number"] = calls[i].to_number;
            callJson["duration"] = calls[i].duration;
            callJson["is_archived"] = calls[i].is_archived;
            callJson["created_at"] = calls[i].created_at;

            response["calls"][i] = std::move(callJson);
        }



        return response;
    });

    CROW_ROUTE(app, "/calls/<int>") ([&repository](int callid) {

        std::optional<Call> call = repository.getCallById(callid);

        if (!call.has_value())
        {
            return crow::response(404, R"({"error":"Call not found"})");
        }
        
        crow::json::wvalue response;

        response["id"] = call->id;
        response["direction"] = (call->direction == Direction::Inbound) ? "inbound" : "outbound";
        response["call_type"] = (call->calltype == CallType::Answered) ? "answered" : (call->calltype == CallType::Missed) ? "missed" : "voicemail";
        response["from_number"] = call->from_number;
        response["to_number"] = call->to_number;
        response["duration"] = call->duration;
        response["is_archived"] = call->is_archived;
        response["created_at"] = call->created_at;
        response["notes"] = crow::json::wvalue::list();

        for (size_t i = 0; i < call->notes.size(); i++)
        {
            crow::json::wvalue noteJson;
            noteJson["id"] = call->notes[i].id;
            noteJson["call_id"] = call->notes[i].call_id;
            noteJson["content"] = call->notes[i].content;

            response["notes"][i] = std::move(noteJson);
        }

        return crow::response(200, response.dump());

    });


    CROW_ROUTE(app, "/calls/<int>/archive").methods(crow::HTTPMethod::PATCH)([&repository](const crow::request& req, int callid) {

        if (!req.body.empty()) {

            auto body = crow::json::load(req.body);

            if (!body)
            {
                return crow::response(400, R"({"error":"Invalid request body"})");
            }
        }

        std::optional<Call> call = repository.archiveCall(callid);

        if (!call.has_value())
        {
            return crow::response(404, R"({"error":"Call not found"})");
        }


        crow::json::wvalue response;

        response["id"] = call->id;
        response["is_archived"]  = call->is_archived;

        return crow::response(200, response.dump());
    });

 /*   //Test for 500 Internal Server Error
    CROW_ROUTE(app, "/test-error")
    ([]() {
    throw std::runtime_error("Test server error");
    return crow::response(200);
    });
*/
    app.port(18080).run();


    return 0;
}