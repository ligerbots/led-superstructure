#include <Wire.h>
int x = 0;
void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);
}

void loop()
{
    if (Serial.available() > 0)
    {
      int incomingByte = Serial.read();
     x = incomingByte - 48;
       Wire.beginTransmission(4); // transmit to device #4
    Wire.write(x);              // sends one byte  
    Wire.endTransmission();    // stop transmitting
    Serial.println("Sent #1");
    }
}
