#include <Servo.h>

Servo servo1;

int pos = 0;

const int LED_PIN = 11;
const int LED_PIN2 = 3;
const int ECHO_PIN = 7;
const int TRIG_PIN = 6;
float duration_echo, cm;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  servo1.attach(4);
}

void loop() {
  digitalWrite(TRIG_PIN, HIGH);
  delay(100);
  digitalWrite(TRIG_PIN, LOW);

  duration_echo = pulseIn(ECHO_PIN, HIGH);
  cm = 0.017 * duration_echo;
  for (pos = 0; pos <= 180; pos += 2) {
    servo1.write(pos);

    if (cm < 5) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    delay(10);
  }

  for (pos = 180; pos >= 0; pos-=2) {
    servo1.write(pos);

    if (cm < 5) {
      digitalWrite(LED_PIN, HIGH);
    } else {
      digitalWrite(LED_PIN, LOW);
    }
    delay(10);
  }
}
