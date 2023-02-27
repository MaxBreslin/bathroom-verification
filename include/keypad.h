#pragma once

#include <vector>
#include <ctime>
#include <string>
#include <wiringPi.h>
#include "../include/client.h"

class Keypad {
public:
    Keypad();
    Keypad(const unsigned int led_pin, const unsigned int submit_button_pin, const std::vector<unsigned int> button_pins, Client * client);
    ~Keypad();

    void set_led_pin(const unsigned int led_pin);
    void set_submit_button_pin(const unsigned int submit_button_pin);
    void set_button_pins(const std::vector<unsigned int> button_pins);
    void set_client(Client * client);

    void on_number_press();
    void on_submit_press();

private:
    const void invert_led();

    unsigned int m_led_pin;
    unsigned int m_submit_button_pin;
    std::vector<unsigned int> m_button_pins;
    std::vector<unsigned int> m_buttons_pressed;
    unsigned int m_last_button_press_time;

    Client * m_client;

    static const unsigned int GAP = 500;
};
