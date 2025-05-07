// Minimal C++ REST API server using cpp-httplib
// This will wrap the SMART Response SDK (DLL + headers)
// Build with: cl /EHsc main.cpp /I../headers SMARTResponseSDK.dll


#include "httplib.h"
#include <iostream>
#include <vector>
#include <string>
#include <mutex>
#include "../headers/smartresponsesdk.h"

// --- Globals for SDK state ---
static smartresponse_connectionV1_t* g_connection = nullptr;
static smartresponse_classV1_t* g_class = nullptr;
static std::vector<sr_student_t*> g_students;
static smartresponse_questionV1_t* g_question = nullptr;
static std::vector<std::string> g_results;
static std::mutex g_mutex;
static bool g_poll_active = false;

// --- Callback for student response ---
extern "C" void on_student_responded(char* id, char* questionId, char* answer, void* aContext) {
    std::lock_guard<std::mutex> lock(g_mutex);
    std::string result = std::string("{\"studentId\":\"") + id + "\",\"answer\":\"" + answer + "\"}";
    g_results.push_back(result);
}

// --- Helper: Create class and students from JSON ---
#include <nlohmann/json.hpp>
using json = nlohmann::json;

bool setup_class_and_students_from_json(const std::string& body, std::string& error) {
    std::lock_guard<std::mutex> lock(g_mutex);
    // Cleanup previous class/students
    for (auto stu : g_students) sr_student_release(stu);
    g_students.clear();
    if (g_class) { sr_class_release(g_class); g_class = nullptr; }

    try {
        auto j = json::parse(body);
        if (!j.contains("className") || !j.contains("students")) {
            error = "Missing className or students";
            return false;
        }
        std::string cname = j["className"];
        if (cname.empty() || cname.size() > 8) {
            error = "Class name must be 1-8 chars";
            return false;
        }
        g_class = sr_class_create((char*)cname.c_str(), (int)cname.size(), false);
        for (const auto& stu : j["students"]) {
            std::string last = stu.value("last", "");
            std::string first = stu.value("first", "");
            std::string id = stu.value("id", "");
            if (last.empty() || first.empty() || id.empty()) continue;
            sr_student_t* s = sr_student_create(last.c_str(), (int)last.size(), first.c_str(), (int)first.size(), id.c_str(), (int)id.size());
            if (sr_class_addstudent(g_class, s) == SR::OK) {
                g_students.push_back(s);
            } else {
                sr_student_release(s);
            }
        }
        if (g_students.empty()) {
            error = "No valid students";
            return false;
        }
        return true;
    } catch (const std::exception& ex) {
        error = ex.what();
        return false;
    }
}

// --- Helper: Setup poll from JSON ---
bool setup_poll_from_json(const std::string& body, std::string& error) {
    std::lock_guard<std::mutex> lock(g_mutex);
    if (g_question) { smartresponse_questionV1_release(g_question); g_question = nullptr; }
    try {
        auto j = json::parse(body);
        std::string qtext = j.value("question", "");
        std::string qtype = j.value("type", "multiplechoice");
        auto choices = j.value("choices", std::vector<std::string>{});
        std::string answer = j.value("answer", "");
        int sdk_type = 0;
        int choice_count = 0;
        if (qtype == "multiplechoice") {
            sdk_type = SMARTRESPONSE_QUESTIONTYPE_MULTIPLECHOICE;
            choice_count = (int)choices.size();
            if (choice_count < 2 || choice_count > 10) {
                error = "Multiple choice: 2-10 choices required";
                return false;
            }
        } else if (qtype == "multipleanswer") {
            sdk_type = SMARTRESPONSE_QUESTIONTYPE_MULTIPLEANSWER;
            choice_count = (int)choices.size();
            if (choice_count < 2 || choice_count > 10) {
                error = "Multiple answer: 2-10 choices required";
                return false;
            }
        } else if (qtype == "yesno") {
            sdk_type = SMARTRESPONSE_QUESTIONTYPE_YESNO;
            choice_count = 2;
        } else if (qtype == "truefalse") {
            sdk_type = SMARTRESPONSE_QUESTIONTYPE_TRUEFALSE;
            choice_count = 2;
        } else if (qtype == "decimal") {
            sdk_type = SMARTRESPONSE_QUESTIONTYPE_DECIMAL;
            choice_count = 0;
        } else if (qtype == "fractional") {
            sdk_type = SMARTRESPONSE_QUESTIONTYPE_FRACTIONAL;
            choice_count = 0;
        } else if (qtype == "shorttext") {
            sdk_type = SMARTRESPONSE_QUESTIONTYPE_SHORTTEXT;
            choice_count = 0;
        } else {
            error = "Unknown question type";
            return false;
        }
        if (qtext.empty()) {
            error = "Question text required";
            return false;
        }
        g_question = smartresponse_questionV1_create(sdk_type, choice_count);
        smartresponse_questionV1_setquestiontext(g_question, (char*)qtext.c_str(), -1);
        if (sdk_type == SMARTRESPONSE_QUESTIONTYPE_MULTIPLECHOICE || sdk_type == SMARTRESPONSE_QUESTIONTYPE_MULTIPLEANSWER) {
            for (size_t i = 0; i < choices.size(); ++i) {
                smartresponse_questionV1_setchoicetext(g_question, (int)i, (char*)choices[i].c_str(), -1);
            }
        }
        if (!answer.empty()) {
            smartresponse_questionV1_setanswer(g_question, (char*)answer.c_str(), -1);
        }
        return true;
    } catch (const std::exception& ex) {
        error = ex.what();
        return false;
    }
}

// --- Helper: Cleanup ---
void cleanup() {
    if (g_question) { smartresponse_questionV1_release(g_question); g_question = nullptr; }
    for (auto stu : g_students) sr_student_release(stu);
    g_students.clear();
    if (g_class) { sr_class_release(g_class); g_class = nullptr; }
    if (g_connection) { smartresponse_connectionV1_release(g_connection); g_connection = nullptr; }
    smartresponse_sdk_terminate();
}

int main() {
    // --- SDK Init ---
    if (!smartresponse_sdk_initialize(1)) {
        std::cerr << "Failed to initialize SMART Response SDK" << std::endl;
        return 1;
    }
    g_connection = smartresponse_connectionV1_create(SMARTRESPONSE_INVOKE_CALLBACKS_ON_MAIN_THREAD_ONLY);
    if (!g_connection) {
        std::cerr << "Failed to create SDK connection" << std::endl;
        smartresponse_sdk_terminate();
        return 1;
    }
    // Connect (async, but we assume instant for demo)
    smartresponse_connectionV1_connect(g_connection);

    httplib::Server svr;

    // --- Setup class/students endpoint ---
    svr.Post("/class/setup", [](const httplib::Request& req, httplib::Response& res) {
        std::string error;
        if (!setup_class_and_students_from_json(req.body, error)) {
            res.status = 400;
            res.set_content(std::string("{\"error\":\"") + error + "\"}", "application/json");
            return;
        }
        res.set_content("{\"status\":\"class setup complete\"}", "application/json");
    });

    svr.Post("/poll/start", [](const httplib::Request& req, httplib::Response& res) {
        std::lock_guard<std::mutex> lock(g_mutex);
        if (g_poll_active) {
            res.set_content("{\"status\":\"already running\"}", "application/json");
            return;
        }
        if (!g_class || g_students.empty()) {
            res.status = 400;
            res.set_content("{\"error\":\"No class/students setup. Use /class/setup first.\"}", "application/json");
            return;
        }
        std::string error;
        if (!setup_poll_from_json(req.body, error)) {
            res.status = 400;
            res.set_content(std::string("{\"error\":\"") + error + "\"}", "application/json");
            return;
        }
        // Start the class
        smartresponse_connectionV2_startclass(g_connection, g_class);
        // Listen for responses
        smartresponse_connectionV1_listenonclickerresponded(g_connection, on_student_responded, nullptr);
        // Start the question
        smartresponse_connectionV1_startquestion(g_connection, g_question);
        g_results.clear();
        g_poll_active = true;
        res.set_content("{\"status\":\"poll started\"}", "application/json");
    });

    svr.Post("/poll/stop", [](const httplib::Request& req, httplib::Response& res) {
        std::lock_guard<std::mutex> lock(g_mutex);
        if (!g_poll_active) {
            res.set_content("{\"status\":\"no poll running\"}", "application/json");
            return;
        }
        smartresponse_connectionV1_stopquestion(g_connection);
        g_poll_active = false;
        res.set_content("{\"status\":\"poll stopped\"}", "application/json");
    });

    svr.Get("/poll/results", [](const httplib::Request& req, httplib::Response& res) {
        std::lock_guard<std::mutex> lock(g_mutex);
        std::string json = "{\"results\":[";
        for (size_t i = 0; i < g_results.size(); ++i) {
            json += g_results[i];
            if (i + 1 < g_results.size()) json += ",";
        }
        json += "]}";
        res.set_content(json, "application/json");
    });

    std::cout << "Server started at http://localhost:8080\n";
    svr.listen("0.0.0.0", 8080);
    cleanup();
    return 0;
}
