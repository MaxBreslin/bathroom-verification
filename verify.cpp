#include <iostream>
#include <wiringPi.h>

// 4 on board -> 7 on wiringPi
// 22 on board -> 3 on wiringPi

int main() {
    wiringPiSetup();

    pinMode(3, OUTPUT);

    pinMode(7, INPUT);
    pullUpDnControl(7, PUD_DOWN);

    bool low = 1;
    uint read = 0;

    while (1) {
        read = digitalRead(7);
        if (read && low) {
            digitalWrite(3, HIGH);
            low = 0;
        }
        else if (!(read || low)) {
            digitalWrite(3, LOW);
            low = 1;
        }

        delay(100);
    }
    return 0;
}
