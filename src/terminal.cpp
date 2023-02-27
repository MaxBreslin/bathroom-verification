
// void on_button() {
//     // Toggle LED
//     digitalWrite(LED, !digitalRead(LED));

//     // Send POST request
//     send_POST();
// }

// void wiringPi_init() {
//     wiringPiSetupGpio();

//     pinMode(LED, OUTPUT);

//     pinMode(BUTTON, INPUT);
//     pullUpDnControl(BUTTON, PUD_DOWN);
// }

// void cleanup(int sig) {
//     // Run when the program is terminated prematurely by Ctrl+C
//     std::cout << "Cleaning up..." << std::endl;
//     exit(sig);
// }

// int main() {
//     std::signal(SIGINT, cleanup);

//     wiringPi_init();

//     // Bind the sendPOST interrupt to the button
//     wiringPiISR(BUTTON, INT_EDGE_FALLING, &on_button);

//     while (1) {
//         // Wait indefinitely for interrupts
//         delay(1000);
//     }

//     return 0;
// }
