#include "../include/keypad.h"

Keypad::Keypad() {
    // Initialize the keypad to default values
    m_led_pin = 0;
    m_submit_button_pin = 0;
    m_button_pins = std::vector<unsigned int>();
    m_buttons_pressed = std::vector<unsigned int>();
    
    m_last_button_press_time = 0;

    // Initialize the client
    m_client = new Client("http://localhost:8000", "none");

    std::cout << "Keypad initialized" << std::endl;
}

Keypad::Keypad(const unsigned int led_pin, const unsigned int submit_button_pin, const std::vector<unsigned int> button_pins, Client * client) {
    // Initialize the keypad to the given values
    m_led_pin = led_pin;
    m_submit_button_pin = submit_button_pin;
    m_button_pins = button_pins;
    m_buttons_pressed = std::vector<unsigned int>();
    
    m_last_button_press_time = 0;

    m_client = client;

    std::cout << "Keypad initialized" << std::endl;
}

Keypad::~Keypad() {
    delete m_client;
}

void Keypad::on_number_press() {
    unsigned int current_time = millis();
    if (current_time - m_last_button_press_time < GAP) {
        std::cout << "Number button pressed too quickly" << std::endl;
        return;
    }

    invert_led();

    m_last_button_press_time = current_time;

    // Loop through the button pins and check for the first high value. If multiple buttons are pressed, only the first one will be registered.
    for (int i = 0; i < m_button_pins.size(); i ++) {
        if (digitalRead(m_button_pins[i])) {
            m_buttons_pressed.push_back(i);
            std::cout << i << " pressed!" << std::endl;
            break;
        }
    }
}

void Keypad::on_submit_press() {
    unsigned int current_time = millis();
    if (current_time - m_last_button_press_time < GAP) {
        std::cout << "Submit button pressed too quickly" << std::endl;
        return;
    }

    invert_led();

    m_last_button_press_time = current_time;

    std::string student_id = "";
    for (unsigned int button : m_buttons_pressed) {
        student_id += std::to_string(button);
    }

    if (student_id == "") {
        std::cout << "No student ID entered" << std::endl;
        return;
    }

    m_buttons_pressed.clear();

    std::string timestamp = std::to_string(std::time(nullptr));

    std::cout << "Asking client to send request with student ID " << student_id << " and timestamp " << timestamp << std::endl;

    m_client->send_request(student_id, timestamp);
}

void Keypad::set_led_pin(const unsigned int led_pin) {
    m_led_pin = led_pin;
}

void Keypad::set_submit_button_pin(const unsigned int submit_button_pin) {
    m_submit_button_pin = submit_button_pin;
}

void Keypad::set_button_pins(const std::vector<unsigned int> button_pins) {
    m_button_pins = button_pins;
}

void Keypad::set_client(Client * client) {
    if (m_client) {
        delete m_client;
    }
    m_client = client;
}

const void Keypad::invert_led() {
    digitalWrite(m_led_pin, !digitalRead(m_led_pin));
}
