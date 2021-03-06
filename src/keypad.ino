/* include Arduino servo library */
#include <Servo.h>

#include "keypad.h"
#include "code.h"

/* code */
const char CODE[CODE_LEN] = {1, 2, 3, 4};

/* servo to open door */
Servo servo;

/* array for user entered code */
int usrCode[CODE_LEN];

/* initialization */
void setup(void) {
    /* set pin modes for all used pins */
    pinMode(BUT_1_PIN,      INPUT);
    pinMode(BUT_2_PIN,      INPUT);
    pinMode(BUT_3_PIN,      INPUT);
    pinMode(BUT_4_PIN,      INPUT);
    pinMode(ENTER_PIN,      INPUT);
    pinMode(LOCKED_LIMIT,   INPUT);
    pinMode(UNLOCKED_LIMIT, INPUT);

    pinMode(LED_PIN, OUTPUT);

    /* attach servo to its pin */
    servo.attach(SERVO_PIN);

    /* set usrCode to all zeroes */
    resetCode();
}

/* continuously called */
void loop(void) {
    servoStop();

    /*servo.write(LOCKED_POS);*/

    /* check if button 1 was pressed */
    checkPin(BUT_1_PIN);

    /* check if button 2 was pressed */
    checkPin(BUT_2_PIN);

    /* check if button 3 was pressed */
    checkPin(BUT_3_PIN);

    /* check if button 4 was pressed */
    checkPin(BUT_4_PIN);

    /* check if enter button was pressed */
    if (digitalRead(ENTER_PIN) == HIGH) {
        do
            delay(10);
        while (digitalRead(ENTER_PIN) == HIGH);

        if (checkCode()) {
            resetCode();
            digitalWrite(LED_PIN, HIGH);

            servo.write(SERVO_CLOCK_WISE);

        do
            delay(10);
        while (digitalRead(UNLOCKED_LIMIT) == LOW);

        servoStop();
        delay(UNLOCK_TIME);

        servo.write(SERVO_COUNT_CLOCK_WISE);

        do
            delay(10);
        while (digitalRead(LOCKED_LIMIT) == LOW);

        digitalWrite(LED_PIN, LOW);
    }
  }
}

bool checkCode(void) {
    int i;

    for (i = 0; i < CODE_LEN; i++)
        if (usrCode[i] != CODE[CODE_LEN - (i + 1)])
            return (false);

    return (true);
}

void checkPin(int pin) {
    if (digitalRead(pin) == HIGH) {
        pushOnCode(pin - 1);

        /* waits for pin to go low */
        do
            delay(10);
        while (digitalRead(pin) == HIGH);
    }
}

void pushOnCode(int n) {
    int i;

    for (i = CODE_LEN - 1; i > 0; i--)
        usrCode[i] = usrCode[i - 1];

        usrCode[0] = n;
}

void resetCode(void) {
    int i;

    for (i = 0; i < CODE_LEN; i++)
        usrCode[i] = 0;
}

void servoStop(void) {
    servo.write(SERVO_STOP);
}
