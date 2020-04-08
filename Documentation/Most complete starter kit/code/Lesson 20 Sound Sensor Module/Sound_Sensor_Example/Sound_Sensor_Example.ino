int  smallSound = A0;         // Select the Arduino input pin to accept the Sound Sensor's analog output 
int  bigSound = A1;           // Select the Arduino input pin to accept the Sound Sensor's analog output 

void setup()
{
  Serial.begin(250000);               
  pinMode(smallSound,INPUT);  
  pinMode(bigSound,INPUT);            
}

void loop(){
  Serial.print(analogRead(smallSound)); // Send the analog value to the serial transmit interface
  Serial.print(" ");
  Serial.println(analogRead(bigSound));   // Send the analog value to the serial transmit interface
  
}
