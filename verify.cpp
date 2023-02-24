#include <iostream>
#include <string>
#include <csignal>
#include <ctime>
#include <wiringPi.h>
#include <curl/curl.h>

#define LED 22
#define BUTTON 26

volatile unsigned long last_request_time = 0;

std::string get_sid() {
    return "000000";
}

std::string get_bathroom_id() {
    return "1";
}

std::string build_POST_request(std::string id, std::string timestamp, std::string bathroom_id) {
    return "sid=" + id + "&timestamp=" + timestamp + "&bathroom-id=" + bathroom_id;
}

bool too_soon(unsigned long current_request_time, unsigned int interval = 3) {
    return current_request_time - last_request_time < interval;
}

void send_POST() {
    std::time_t now = std::time(nullptr);
    unsigned long current_request_time = static_cast<unsigned long>(now);
    
    // Check if this request is too soon (mostly to prevent button bounce during testing, but will be helpful later on)
    if (too_soon(current_request_time)) {
        std::cout << "Request triggered too early (Last request: " << last_request_time << " / Current request: " << current_request_time << ")" << std::endl;
        return;
    }

    last_request_time = current_request_time;

    CURL * curl;
    CURLcode res;

    std::string post_fields = build_POST_request(get_sid(), std::to_string(now), get_bathroom_id());

    // Initialize the curl object
    curl = curl_easy_init();
    if (curl) {
        // Set the URL and POST fields
        curl_easy_setopt(curl, CURLOPT_URL, "http://localhost:8000");
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, post_fields.c_str());

        // Perform the request and store the result in res
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            // Failed to perform request (e.g. no internet connection or server is down)
            std::cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << std::endl;
        }

        // Cleanup the curl object
        curl_easy_cleanup(curl);
    }
    else {
        // Failed to initialize curl object (unlikely)
        std::cerr << "curl_easy_init() failed" << std::endl;
    }
}

void on_button() {
    // Toggle LED
    digitalWrite(LED, !digitalRead(LED));

    // Send POST request
    send_POST();
}

void wiringPi_init() {
    wiringPiSetupGpio();

    pinMode(LED, OUTPUT);

    pinMode(BUTTON, INPUT);
    pullUpDnControl(BUTTON, PUD_DOWN);
}

void cleanup(int sig) {
    // Run when the program is terminated prematurely by Ctrl+C
    std::cout << "Cleaning up..." << std::endl;
    exit(sig);
}

int main() {
    std::signal(SIGINT, cleanup);

    wiringPi_init();

    // Bind the sendPOST interrupt to the button
    wiringPiISR(BUTTON, INT_EDGE_FALLING, &on_button);

    while (1) {
        // Wait indefinitely for interrupts
        delay(1000);
    }

    return 0;
}
