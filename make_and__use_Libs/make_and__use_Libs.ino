#include "test_library.h"
void setup() 
{
  Serial.begin(9600);
  Serial.println("SETUP");
}
void loop() {
  int result = addPrevInt(1);
  Serial.println(result);
}
