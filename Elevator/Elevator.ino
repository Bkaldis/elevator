#include <Simulation.h>


//libraries
//choose one of the libraries BUT NOT BOTH



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


//Global Variables
int target;
bool UP = false;
bool DOWN = false;
bool targets[] = {0, 0, 0, 0, 0};
long dist = 45;
const int FLn[] = {3, 15, 31, 45, 60};
bool oned;
int motion = 0;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Serial.println("setup");
  //---set pin input vs output
  
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRU, OUTPUT);
  pinMode(DIRD, OUTPUT);
  pinMode(LED0, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(LED4, OUTPUT);
}

void loop() {
  //inputs
  if (buttons() != 0) {
    push(buttons() - 1);
  }
  dist = distance();

  //computations need to take in buttons and distance and give bool LEDs[] and int motion
  target = nextTarget();
  setMotion();

  //outputs
  LEDsDriver(targets);
  MotorDriver(motion);
}


int push(int num) {//add a new targets to targets[]
  if (num >= 0 and num <= 4) {
    Serial.print("  in push()");
    Serial.print(num);
    Serial.print("  ");
    targets[num] = 1;
  }
}


int pop(int num) {//remove a target from targets[]
  Serial.print("in pop()");
  target = nextTarget();
  targets[num] = 0;
}



int nextTarget() {//choose the next target
  target = -1;
  int count = -1;
  int current = -1;
  Serial.print(" count:");
  Serial.print(count);
  Serial.print(" current:");
  Serial.print(current);

  for (int i = 0; i < 5; i++) { //this is to determine the current floor DON'T change after this
    if (dist >= FLn[i] and dist < FLn[i + 1]) {
      count = i; //iterate through targs[]
      current = i; //know where we started
    }
    if (oned == true) { //we look up first then down
      for (int i = current + 1; i <= 4; i++) { //start at the space after current
        if (targets[i] == 1) {
          return i;
        }
      }
      for (int i = current - 1; i >= 0; i--) { //start at the space before current
        if (targets[i] == 1) {
          return i;
        }
      }
    }
    if (oned == false) { //we look down first then up
      for (int i = current - 1; i >= 0; i--) { //start at the space before current
        if (targets[i] == 1) {
          return i;
        }
      }
      for (int i = current + 1; i <= 4; i++) { //start at the space after current
        if (targets[i] == 1) {
          return i;
        }
      }
    }
  }
  Serial.print(" count:");
  Serial.print(count);
  Serial.print(" current:");
  Serial.print(current);
}

void setMotion() {
  if (dist == FLn[target]) {//we want to stop
    motion = 0;
    Serial.print("STOP");
    pop(dist);
  } else if (dist < FLn[target] or dist == 0) {//we want to go up
    motion = 1;
    Serial.print("UP");
  } else if (dist > FLn[target] or dist == 60) {//we want to go down
    motion = -1;
    Serial.print("DOWN");
  }else{
    motion = 0;
  }
}
