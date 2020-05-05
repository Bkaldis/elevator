#include "SR04.h"
#include "Hardware.h"

//pins
#define ENABLE 5
#define DIRD 4
#define DIRU 3
#define LED0 51
#define LED1 50
#define LED2 49
#define LED3 48
#define LED4 47
#define TRIG_PIN 12//ultrasonic sensor
#define ECHO_PIN 11//ultrasonic sensor



//rename a function in SR04.h
SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);//rename ultra sonic sensor library

String motion = "";
int dist = 0;
int buttons() {
  float val = analogRead(A0);
  return round(val);
}
int distance() {
  dist = sr04.Distance();
  return dist;
}
void LEDsDriver(bool* LEDs) {
  digitalWrite(LED0, LEDs[0]);
  digitalWrite(LED1, LEDs[1]);
  digitalWrite(LED2, LEDs[2]);
  digitalWrite(LED3, LEDs[3]);
  digitalWrite(LED4, LEDs[4]);
}
void MotorDriver(String motion) {
  if (motion == "UP") {
    Serial.print("UP");
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRU, HIGH);
    digitalWrite(DIRD, LOW);
  } else if (motion == "DOWN") {
    Serial.print("DOWN");
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, HIGH);
  } else if (motion == "STOP") {
    Serial.print("STOP");
    digitalWrite(ENABLE, LOW);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, LOW);
  } else {
    Serial.print("ERROR in MotorDriver() motion = ");
    Serial.print(motion);
    digitalWrite(ENABLE, LOW);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, LOW);
  }
}
