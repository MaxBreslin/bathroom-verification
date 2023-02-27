#include "../include/client.h"

Client::Client() {
    // Initialize the curl object
    m_curl = curl_easy_init();
    if (!m_curl) {
        // Failed to initialize curl object (unlikely)
        std::cerr << "curl_easy_init() failed" << std::endl;
    }

    m_server_url = "http://localhost:8000";
    m_bathroom_id = "none";

    curl_easy_setopt(m_curl, CURLOPT_URL, m_server_url.c_str());
}

Client::Client(const std::string server_url, const std::string bathroom_id) {
    // Initialize the curl object
    m_curl = curl_easy_init();
    if (!m_curl) {
        // Failed to initialize curl object (unlikely)
        std::cerr << "curl_easy_init() failed" << std::endl;
    }

    m_server_url = server_url;
    m_bathroom_id = bathroom_id;

    curl_easy_setopt(m_curl, CURLOPT_URL, m_server_url.c_str());

    std::cout << "Client initialized with server URL " << m_server_url << " and bathroom ID " << m_bathroom_id << std::endl;
}

Client::~Client() {
    // Cleanup the curl object
    curl_easy_cleanup(m_curl);
}

void Client::send_request(const std::string student_id, const std::string timestamp) {
    if (!m_curl) {
        // curl object was not initialized
        std::cerr << "FATAL! m_curl is not initialized" << std::endl;
        return;
    }

    unsigned int current_time = static_cast<unsigned int>(std::time(nullptr));
    
    // Check if this request is too soon
    if (current_time - m_last_request_time < GAP) {
        std::cout << "Request triggered too early (Last request: " << m_last_request_time << " / Current request: " << current_time << ")" << std::endl;
        return;
    }

    m_last_request_time = current_time;

    CURLcode res;

    std::string post_fields = build_request(student_id, timestamp);

    curl_easy_setopt(m_curl, CURLOPT_POSTFIELDS, post_fields.c_str());

    std::cout << "Sending request to " << m_server_url << " with data: " << post_fields << std::endl;
    // Perform the request and store the result in res
    res = curl_easy_perform(m_curl);
    if (res != CURLE_OK) {
        // Failed to perform request (e.g. no internet connection or server is down)
        std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
    }
}

void Client::set_server_url(const std::string server_url) {
    m_server_url = server_url;
    curl_easy_setopt(m_curl, CURLOPT_URL, m_server_url);
}

const std::string Client::get_server_url() {
    return m_server_url;
}

void Client::set_bathroom_id(const std::string bathroom_id) {
    m_bathroom_id = bathroom_id;
}

const std::string Client::get_bathroom_id() {
    return m_bathroom_id;
}

const unsigned int Client::get_last_request_time() {
    return m_last_request_time;
}

const std::string Client::build_request(const std::string student_id, const std::string timestamp) {
    return "student-id=" + student_id + "&timestamp=" + timestamp + "&bathroom-id=" + m_bathroom_id;
}
