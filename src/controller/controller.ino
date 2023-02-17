#include <Wire.h>
int x = 0;
void setup()
{
  Wire.begin(); // join i2c bus (address optional for master)
  Serial.begin(9600);

}


void loop()
{
  Wire.beginTransmission(4); // transmit to device #4
  Wire.write(x);              // sends one byte  
  Wire.endTransmission();    // stop transmitting
  
  Serial.print(x);

  x++;
  if(x>4){
    x=0;
  }
  delay(10000);
}
