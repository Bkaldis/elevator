#include <stdio.h>

#define ENABLE 5
#define DIRU 3
#define DIRD 4
#define FLOOR0 51
#define FLOOR1 50
#define FLOOR2 49
#define FLOOR3 48
#define FLOOR4 47
#define FLOOR5 46

int FLOORcurrent = 4;
int target = -1;
bool UP = false;
bool DOWN = false;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("setup");
  //---set pin direction
  pinMode(ENABLE,OUTPUT);
  pinMode(DIRU,OUTPUT);
  pinMode(DIRD,OUTPUT);
  pinMode(FLOOR0, INPUT);
  pinMode(FLOOR1, INPUT);
  pinMode(FLOOR2, INPUT);
  pinMode(FLOOR3, INPUT);
  pinMode(FLOOR4, INPUT);
  pinMode(FLOOR5, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.print(FLOORcurrent);
//  Serial.print("  ");
//  Serial.println(target);
  
  bool selected = digitalRead(FLOOR0) or digitalRead(FLOOR1) or digitalRead(FLOOR2) or digitalRead(FLOOR3) or digitalRead(FLOOR4) or digitalRead(FLOOR5);
  
  if(selected == true){
    Serial.print(FLOORcurrent);
    Serial.print("  ");
    Serial.println(target);
    //Serial.println("button");
    if (digitalRead(FLOOR0) == true){
      target = push(0);
    }
    else if (digitalRead(FLOOR1) == true){
      target = push(1);
    }
    else if (digitalRead(FLOOR2) == true){
      target = push(2);
    }
    else if (digitalRead(FLOOR3) == true){
      target = push(3);
    }
    else if (digitalRead(FLOOR4) == true){
      target = push(4);
    }
    else if (digitalRead(FLOOR5) == true){
      target = push(5);
    }
    dir();
  }
}

int push(int num){
  Serial.print("in push()");
  Serial.print(num);
  Serial.print("  ");
  return num;
}


int pop(){
  //Serial.print("in pop()");
  target = -1;
  
}

int dir(){
  if(FLOORcurrent < target){
    digitalWrite(ENABLE,HIGH);
    digitalWrite(DIRU,HIGH);
    digitalWrite(DIRD,LOW);
    //FLOORcurrent = FLOORcurrent +1;
  }
  else if(FLOORcurrent > target){
    digitalWrite(ENABLE,HIGH);
    digitalWrite(DIRU,LOW);
    digitalWrite(DIRD,HIGH);
    //FLOORcurrent = FLOORcurrent -1;
  }
  else if(FLOORcurrent = target){
    digitalWrite(ENABLE,LOW); 
    digitalWrite(DIRU,LOW);
    digitalWrite(DIRD,LOW);
    pop();
  }
  else{
    digitalWrite(ENABLE,LOW); 
    digitalWrite(DIRU,LOW);
    digitalWrite(DIRD,LOW);
    //Serial.print("in dir() else statment ERROR!!!");
  }
}
