
#ifndef KEYPAD_H

#define KEYPAD_H

/* number of digits in code */
#define CODE_LEN 4

/* define pins associated with buttons */
#define BUT_1_PIN 2    /* prp */
#define BUT_2_PIN 3    /* blu */
#define BUT_3_PIN 4    /* grn */
#define BUT_4_PIN 5    /* ylw */
#define ENTER_PIN 6    /* org */

/* define pins for limit switches */
#define LOCKED_LIMIT   7
#define UNLOCKED_LIMIT 8

/* define other pins */
#define LED_PIN   13
#define SERVO_PIN 12

/* define servo attributes */
#define UNLOCK_TIME            3000
#define SERVO_STOP             91
#define SERVO_CLOCK_WISE       30
#define SERVO_COUNT_CLOCK_WISE 150

#endif
