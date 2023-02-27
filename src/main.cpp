#include "../include/main.h"

#define LED_PIN 22
#define SUBMIT_BUTTON_PIN 26
#define NUMBER_1_PIN 16
#define NUMBER_2_PIN 20
#define NUMBER_3_PIN 21

Client * client = nullptr;
Keypad * keypad = nullptr;

int main() {

    std::vector<unsigned int> number_pins = {NUMBER_1_PIN, NUMBER_2_PIN, NUMBER_3_PIN};

    wiringPiSetupGpio();
    std::signal(SIGINT, cleanup);

    client = new Client("http://localhost:8000", "none");
    keypad = new Keypad(LED_PIN, SUBMIT_BUTTON_PIN, number_pins, client);

    std::cout << "Initializing pins and interrupts..." << std::endl;
    initialize_pins(number_pins);
    initialize_interrupts(number_pins);

    // Wait for interrupts
    while (1) {
        delay(1000);
    }
    
    delete keypad;

    return 0;
}

void cleanup(int sig) {
    // Run when the program is terminated prematurely by Ctrl+C
    std::cout << "Cleaning up..." << std::endl;
    delete keypad;
    exit(sig);
}

void on_number_press() {
    keypad->on_number_press();
}
void on_submit_press() {
    keypad->on_submit_press();
}

void initialize_interrupts(std::vector<unsigned int> number_pins) {
    // Set the submit button pin to interrupt on rising edge
    wiringPiISR(SUBMIT_BUTTON_PIN, INT_EDGE_RISING, &on_submit_press);

    // Set the number pins to interrupt on rising edge
    for (unsigned int pin : number_pins) {
        wiringPiISR(pin, INT_EDGE_RISING, &on_number_press);
    }
}

void initialize_pins(std::vector<unsigned int> number_pins) {
    // Set the submit button pin to input
    pinMode(SUBMIT_BUTTON_PIN, INPUT);

    // Set the submit button pin to pull down
    pullUpDnControl(SUBMIT_BUTTON_PIN, PUD_DOWN);

    for (unsigned int pin : number_pins) {
        pinMode(pin, INPUT);
        pullUpDnControl(pin, PUD_DOWN);
    }

    // Set the LED pin to output
    pinMode(LED_PIN, OUTPUT);

    // Set the LED pin to low
    digitalWrite(LED_PIN, HIGH);
}
