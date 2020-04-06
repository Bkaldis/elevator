#include <stdio.h>
#include "SR04.h"

#define ENABLE 5
#define DIRU 3
#define DIRD 4
#define FLOOR0 51
#define FLOOR1 50
#define FLOOR2 49
#define FLOOR3 48
#define FLOOR4 47
#define TRIG_PIN 12
#define ECHO_PIN 11

SR04 sr04 = SR04(ECHO_PIN, TRIG_PIN);

int FLOORcurrent = -1;
int target = 2;
bool UP = false;
bool DOWN = false;
long dist;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("setup");
  //---set pin direction
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRU, OUTPUT);
  pinMode(DIRD, OUTPUT);
  pinMode(FLOOR0, INPUT);
  pinMode(FLOOR1, INPUT);
  pinMode(FLOOR2, INPUT);
  pinMode(FLOOR3, INPUT);
  pinMode(FLOOR4, INPUT);
}

void loop() {
  Serial.println();
  // put your main code here, to run repeatedly:

  bool selected = digitalRead(FLOOR0) or digitalRead(FLOOR1) or digitalRead(FLOOR2) or digitalRead(FLOOR3) or digitalRead(FLOOR4);

  dist = sr04.Distance();
  Serial.print(dist);
  if(dist < 15){
    dist = dist -3;
  }if(dist >55){
    dist = dist +3;
  }
  Serial.print("cm   ");
  Serial.print("FL");
  FLOORcurrent = floor((dist)/15);
  Serial.print(FLOORcurrent);
  Serial.print("  ");
  Serial.print("T:");
  Serial.print(target);
  Serial.print("  ");
  if (selected == true) {
    //Serial.println("button");
    if (digitalRead(FLOOR0) == true) {
      target = push(0);
    }
    else if (digitalRead(FLOOR1) == true) {
      target = push(1);
    }
    else if (digitalRead(FLOOR2) == true) {
      target = push(2);
    }
    else if (digitalRead(FLOOR3) == true) {
      target = push(3);
    }
    else if (digitalRead(FLOOR4) == true) {
      target = push(4);
    }
    
  }
  dir();
}

int push(int num) {
  Serial.print("in push()");
  Serial.print(num);
  Serial.print("  ");
  return num;
}


int pop() {
  //Serial.print("in pop()");
  //target = -1;

}

int dir() {
  if (FLOORcurrent < target or FLOORcurrent == 0) {
    Serial.print("UP");
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRU, HIGH);
    digitalWrite(DIRD, LOW);
    
  }
  else if (FLOORcurrent > target or FLOORcurrent == 4) {
    Serial.print("DOWN");
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, HIGH);
    
  }
  else if (FLOORcurrent = target) {
    Serial.print("STOP");
    digitalWrite(ENABLE, LOW);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, LOW);
    //pop();
  }
}
