#include "Simulation.h"

int dist = 0;
int direction= 0;

int buttons () {
  if ( random(1, 10) <= 1) {
    int val = random(1, 5);
    return val;
  }
}

int distance () {
  if (direction == 1 ) {
    dist = dist + 1;
  } else if (direction == -1) {
    dist = dist - 1;
  } else if (direction == 0) {
    dist = dist;
    return dist;
  }
}

void LEDsDriver(bool* LEDs){
  for (int i = 0; i <= 4; i++) {
    Serial.print(LEDs[i]);
  }
}

void MotorDriver (int motion) {
	if(motion == -1 or 0 or 1){
		direction = motion;
		Serial.print(direction);
	}else{
		direction = 0;
		Serial.print("ERROR");
	}
}