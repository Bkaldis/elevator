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
int target;
bool UP = false;
bool DOWN = false;
bool targets[] = {0,0,0,0,0};
long dist = 45;
const int FLn[] = {3, 15, 31, 45, 60};
bool oned;


void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println();
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

  print();

  
  simINS();
  
  
  
  simDIR();
}



int push(int num) {
  Serial.print("  in push()");
  Serial.print(num);
  Serial.print("  ");
  targets[num] = 1;
}


int pop(int num) {
  Serial.print("in pop()");
  target = algor(targets, dist, oned);
  targets[num] = 0;
}

int simDIR(){
  Serial.print("  ");
  Serial.print(dist);
  Serial.print("  ");
  Serial.print(target);
  Serial.print("  ");
  Serial.print(FLn[target]);
  Serial.print("  ");
  if (dist = FLn[target]) {
    Serial.print("sim-STOP");
    pop(dist);
  }
  else if (dist < FLn[target] or dist == 0) {
    Serial.print("sim-UP");
    oned = true;
    dist = dist + 1;
  }
  else if (dist > FLn[target] or dist == 60) {
    Serial.print("sim-DOWN");
    oned = false;
    dist=dist - 1;
  }
}


int hardDIR(int dist) {
  Serial.print("  ");
  Serial.print(dist);
  Serial.print("  ");
  Serial.print(target);
  Serial.print("  ");
  Serial.print(FLn[target]);
  Serial.print("  ");
  if (dist = FLn[target]) {
    Serial.print("STOP");
    digitalWrite(ENABLE, LOW);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, LOW);
    pop(dist);
  }
  else if (dist < FLn[target] or dist == 0) {
    Serial.print("UP");
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRU, HIGH);
    digitalWrite(DIRD, LOW);
    
  }
  else if (dist > FLn[target] or dist == 60) {
    Serial.print("DOWN");
    digitalWrite(ENABLE, HIGH);
    digitalWrite(DIRU, LOW);
    digitalWrite(DIRD, HIGH);
  }
   
}



int algor(bool targets[],int dist, bool oned){
  int count = floor(dist/15);
  if(oned == true){//we want to look up
    while(targets[count]==0){
      count=count +1;
      target = count;
    }
  }
  else if(oned == false){//we want to look down
    while(targets[count]==0){
      count=count-1;
      target = count;
    }
  }
  else{
    target=0;
  }
  return target;
}

int hardINS(){
  dist = sr04.Distance();
  
  bool selected = digitalRead(FLOOR0) or digitalRead(FLOOR1) or digitalRead(FLOOR2) or digitalRead(FLOOR3) or digitalRead(FLOOR4);

  if (selected == true) {
    //Serial.println("button");
    if (digitalRead(FLOOR0) == true) {
      push(0);
    }
    else if (digitalRead(FLOOR1) == true) {
      push(1);
    }
    else if (digitalRead(FLOOR2) == true) {
      push(2);
    }
    else if (digitalRead(FLOOR3) == true) {
      push(3);
    }
    else if (digitalRead(FLOOR4) == true) {
      push(4);
    }
  }
}

int simINS(){
  if(random(0,100) < 1){
    int num = random(0,5);
    Serial.print(num);
    push(num);
  }
}


int print(){
  Serial.print(dist);
  if(dist < 15){
    dist = dist -4;
  }
  Serial.print("cm   ");
  Serial.print("FLn: ");
  Serial.print(FLn[0]);
  Serial.print(FLn[1]);
  Serial.print(FLn[2]);
  Serial.print(FLn[3]);
  Serial.print(FLn[4]);
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
