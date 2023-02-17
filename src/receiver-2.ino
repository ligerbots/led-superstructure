#include <Wire.h>

int address = 4;

int rChannelF = 0;
int gChannelF = 0;
int bChannelF = 0;

int rChannelB = 0;
int gChannelB = 0;
int bChannelB = 0;

enum redChannel {
	off = 0,
	green = 0,
	red = 255,
	purple = 255,
	yellow = 255,
	orange = 246
}

enum greenChannel {
	off = 0,
	green = 255,
	red = 0,
	purple = 0,
	yellow = 255,
	orange = 134
}

enum blueChannel {
	off = 0,
	green = 0,
	red = 0,
	purple = 255,
	yellow = 0,
	orange = 51
}

#define rPin 3
#define gPin 5
#define bPin 6  

#define rPin2 9
#define gPin2 10
#define bPin2 11 

int x = 0;


int bytesRecived = 0;

void setup() {
  Wire.begin(4);
  Serial.begin(9600);
}


void loop() {

  Wire.onReceive(receiveEvent);
  
  switch (x)
  {
  //check for off mode
    case 0:
      rChannelF = redChannel::off;
      gChannelF = greenChannel::off;
      bChannelF = blueChannel::off;
	  
	  rChannelB = redChannel::off;
      gChannelB = greenChannel::off;
      bChannelB = blueChannel::off;
      break;
  
  //check for purple/green mode
    case 1:
      rChannelF = redChannel::purple;
      gChannelF = greenChannel::purple;
      bChannelF = blueChannel::purple;
	  
	  rChannelB = redChannel::green;
      gChannelB = greenChannel::green;
      bChannelB = blueChannel::green;
      break;
  
  //Check for purple/red mode
    case 3:
      rChannelF = redChannel::purple;
      gChannelF = greenChannel::purple;
      bChannelF = blueChannel::purple;
	  
	  rChannelB = redChannel::red;
      gChannelB = greenChannel::red;
      bChannelB = blueChannel::red;
      break;
  
  //check for yellow/green mode
    case 5:
      rChannelF = redChannel::yellow;
      gChannelF = greenChannel::yellow;
      bChannelF = blueChannel::yellow;
	  
	  rChannelB = redChannel::green;
      gChannelB = greenChannel::green;
      bChannelB = blueChannel::green;
      break;

  //check for yellow/red mode
    case 7:
      rChannelF = redChannel::yellow;
      gChannelF = greenChannel::yellow;
      bChannelF = blueChannel::yellow;
	  
	  rChannelB = redChannel::red;
      gChannelB = greenChannel::red;
      bChannelB = blueChannel::red;
      break;
	  
  //check for orange mode
    case 9:
      rChannelF = redChannel::orange;
      gChannelF = greenChannel::orange;
      bChannelF = blueChannel::orange;
	  
	  rChannelB = redChannel::orange;
      gChannelB = greenChannel::orange;
      bChannelB = blueChannel::orange;
      break;
  }

  outputToLED(rChannelF, gChannelF, bChannelF, rChannelB, gChannelB, bChannelB);
}

void outputToLED(int rOutF, int gOutF, int bOutF, int rOutB, int gOutB, int bOutB) {
  
  analogWrite(rPin, rOutF);
  analogWrite(gPin, gOutF);
  analogWrite(bPin, bOutF);
  
  analogWrite(rPin2, rOutB);
  analogWrite(gPin2, gOutB);
  analogWrite(bPin2, bOutB);
}

void receiveEvent(int howMany)
{
  x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}