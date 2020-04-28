#include <stdio.h>
#include "SR04.h"

#define ENABLE 5//Motor enable
#define DIRU 3//Motor up
#define DIRD 4//Motor down
#define LED0 51//LEDs to show targets[]
#define LED1 50
#define LED2 49
#define LED3 48
#define LED4 47
#define TRIG_PIN 12//ultrasonic sensor
#define ECHO_PIN 11//ultrasonic sensor
#define Bselect PIN_A0

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);//rename ultra sonic sensor library

int target = 2;//the next floor to go to
bool UP = false;//motor direction
bool DOWN = false;//motor direction
bool targets[] = {0, 0, 1, 0, 0}; //all selected floors
long dist = 45;//this is our "meter stick"
const int FLn[] = {3, 15, 31, 45, 60};//desiered distance for each floor
bool oned;//this is how we keep track of the direction we look to choose next target


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
  Serial.println("setup");
  //---set pin input vs output
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRU, OUTPUT);
  pinMode(DIRD, OUTPUT);
  pinMode(LED0, INPUT);
  pinMode(LED1, INPUT);
  pinMode(LED2, INPUT);
  pinMode(LED3, INPUT);
  pinMode(LED4, INPUT);
}

void loop() {
  Serial.println();
  // put your main code here, to run repeatedly:


  //print();//our print function prints out all variables


  //simINS();//simulated inputs
  hardINS();//hardware inputs


  //dist = simDIR();//simulated motor driver
  dist = hardDIR();//hardware motor driver
}



int push(int num) {//add a new targets to targets[]
  Serial.print("  in push()");
  Serial.print(num);
  Serial.print("  ");
  targets[num] = 1;
}


int pop(int num) {//remove a target from targets[]
  Serial.print("in pop()");
  target = nextTarget();
  targets[num] = 0;
}

int simDIR() {
  Serial.print("  before dist: ");//print function variables
  Serial.print(dist);
  Serial.print("  Target:");
  Serial.print(target);
  Serial.print("  FLn[target]:");
  Serial.print(FLn[target]);
  Serial.print("  ");
  if (dist == FLn[target] or dist <= FLn[0] or dist >= FLn[4]) {//we want to stop
    Serial.print("sim-STOP");
    pop(dist);
  }
  else if (dist < FLn[target] or dist == 0) {//we want to go up
    Serial.print("sim-UP");
    oned = true;
    dist = dist + 1;
  }
  else if (dist > FLn[target] or dist == 60) {//we want to go down
    Serial.print("sim-DOWN");
    oned = false;
    dist = dist - 1;
  }
  Serial.print("  after dist: ");//print function variables
  Serial.print(dist);
  Serial.print("  ");
  return dist;
}


int hardDIR() {
  Serial.print("  ");//function prints
  Serial.print(dist);
  Serial.print("  ");
  Serial.print(target);
  Serial.print("  ");
  Serial.print(FLn[target]);
  Serial.print("  ");
  if (dist == FLn[target]) {//we want to stop
    Serial.print("STOP");
    digitalWrite(ENABLE, LOW);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, LOW);
    pop(dist);
  }
  else if (dist < FLn[target] or dist == 0) {//we want to go up
    Serial.print("UP");
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRU, HIGH);
    digitalWrite(DIRD, LOW);

  }
  else if (dist > FLn[target] or dist == 60) {//we want to go down
    Serial.print("DOWN");
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, HIGH);
  }
  return dist;
}



int nextTarget() {
  target = -1;

  Serial.print("IN NEXT TARGET FUNCTION!!!  ");
  Serial.print("old target: ");
  Serial.print(target);
  //int count = floor(dist/15);

  int count = -1;
  for (int i = 1; i < 4; i++) { //do this 4 times
    if ((dist >= FLn[i - 1]) and (dist < FLn[i])) { //is dist between FLn[i-1] and FLn[i]
      count = count + 1;
    }
  }

  if (oned == true) { //we want to look up for our next target
    Serial.print(" oned is true ");
    while (targets[count] == 0) {
      Serial.print("LOOKING UP!!  ");
      count = count + 1;
      target = count;
    }
    oned = false; //Change direction
  }
  else if (oned == false) { //we want to look down for our next target
    Serial.print(" oned is false ");
    while (targets[count] == 0) {
      Serial.print("LOOKING DOWN!!  ");
      count = count - 1;
      target = count;
    }
    oned = true; //Change direction
  }
  else {
    Serial.print("IDK WHERE TO LOOK!!  ");
    target = 0;
  }

  Serial.print("new target: ");
  Serial.print(target);
  return target;
}

int hardINS() {
  dist = sr04.Distance();
  
  //get distance from ultrasonic sensor

  push(round(analogRead(Bselect) / 5));
  //read analog pin 5V, 5 resistor voltade divider w/ button at each node
  //send to targets[] by push()
}

int simINS() {
  if (random(0, 10) < 1) { //10% of the time simulate a button press
    int num = random(0, 5); //choose random "button"
    Serial.print(num);
    push(num);
    //send to targets[] by push()
  }
}


int print() { //to print while debugging
  Serial.print(dist);
  Serial.print("cm   ");
  Serial.print("FLn[target]: ");
  Serial.print(FLn[target]);
  Serial.print("  Targs: ");
  Serial.print(targets[0]);
  Serial.print(targets[1]);
  Serial.print(targets[2]);
  Serial.print(targets[3]);
  Serial.print(targets[4]);
  Serial.print("  T:");
  Serial.print(target);
  Serial.print("  ");
  Serial.print("oned: ");
  Serial.print(oned);
  Serial.print("  ");
}
