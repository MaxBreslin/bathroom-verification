#pragma once

#include <iostream>
#include <csignal>
#include <wiringPi.h>

#include "../include/client.h"
#include "../include/keypad.h"

int main();

void on_number_press();
void on_submit_press();

void initialize_interrupts(std::vector<unsigned int> number_pins);
void initialize_pins(std::vector<unsigned int> number_pins);

void cleanup(int sig);
