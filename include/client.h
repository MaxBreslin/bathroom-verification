#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <curl/curl.h>

class Client {
public:
    Client();
    Client(const std::string server_url, const std::string bathroom_id);
    ~Client();

    void send_request(const std::string student_id, const std::string timestamp);

    void set_server_url(const std::string server_url);
    const std::string get_server_url();
    void set_bathroom_id(const std::string bathroom_id);
    const std::string get_bathroom_id();
    const unsigned int get_last_request_time();

private:
    const std::string build_request(const std::string student_id, const std::string timestamp);

    CURL * m_curl;
    std::string m_server_url;
    std::string m_bathroom_id;
    unsigned int m_last_request_time;

    static const unsigned int GAP = 3;
};
