#include <Servo.h>
#include <LiquidCrystal.h>

Servo servo1;
LiquidCrystal lcd(13,12,10,9,8,5);

int pos = 0;

const int LED_PIN = 11;
const int LED_PIN2 = 3;
const int ECHO_PIN = 7;
const int TRIG_PIN = 6;
float duration_echo, cm;

unsigned long previousServoMillis = 0;
unsigned long previousDistanceMillis = 0;
const long servoInterval = 10;    // Delay interval for servo movement (in milliseconds)
const long distanceInterval = 100; 

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(LED_PIN2, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  pinMode(TRIG_PIN, OUTPUT);
  servo1.attach(4);
  lcd.begin(16,2);
}

void loop() {
  unsigned long currentMillis = millis();

  // Move servo gradually
  if (currentMillis - previousServoMillis >= servoInterval) {
    previousServoMillis = currentMillis;
    moveServo();
  }

  // Check distance periodically
  if (currentMillis - previousDistanceMillis >= distanceInterval) {
    previousDistanceMillis = currentMillis;
    checkDistance();
  }
}

void moveServo() {
  if (pos <= 180) {
    servo1.write(pos);
    pos += 1;
  } else {
    pos = 0;
  }
}

void checkDistance() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);

  duration_echo = pulseIn(ECHO_PIN, HIGH);
  cm = 0.017 * duration_echo;

  if (cm < 10) {
    digitalWrite(LED_PIN, HIGH);
  } else {
    digitalWrite(LED_PIN, LOW);
  }

  lcd.setCursor(0,0);
  lcd.print(cm);
}
