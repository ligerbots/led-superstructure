#include <Wire.h>

int address = 4;

int rChannel = 0;
int gChannel = 0;
int bChannel = 0;

#define rPin 3
#define gPin 5
#define bPin 6

#define rPin2 9
#define gPin2 10
#define bPin2 11

int incomingByte = 0; // for incoming serial data

int x = 0;

int bytesRecived = 0;

void setup()
{
    pinMode(rPin, OUTPUT);
    pinMode(gPin, OUTPUT);
    pinMode(bPin, OUTPUT);
    pinMode(rPin2, OUTPUT);
    pinMode(gPin2, OUTPUT);
    pinMode(bPin2, OUTPUT);
    Wire.begin(4);
    Serial.begin(9600);
}

void loop()
{
    // Wire.onReceive(receiveEvent);
    // send data only when you receive data:
    if (Serial.available() > 0) {
      // read the incoming byte:
      incomingByte = Serial.read();
      
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
    }
    x = incomingByte - 48;
    switch (x)
    {
        // check for off mode
    case 0:
        rChannel = 0;
        gChannel = 0;
        bChannel = 0;
        break;

        // check for purple mode
    case 1:
        rChannel = 194;
        gChannel = 0;
        bChannel = 242;
        break;

        // Check for yellow mode
    case 2:
        rChannel = 255;
        gChannel = 120;
        bChannel = 0;
        break;

        // check for orange mode
    case 3:
        rChannel = 255;
        gChannel = 50;
        bChannel = 0;
        break;

        // set default as Off
    default:
        rChannel = 0;
        gChannel = 0;
        bChannel = 0;
        break;
    }

    outputToLED(rChannel, gChannel, bChannel);
}

void outputToLED(int rOut, int gOut, int bOut)
{
    analogWrite(rPin, rOut);
    analogWrite(gPin, gOut);
    analogWrite(bPin, bOut);
    analogWrite(rPin2, rOut);
    analogWrite(gPin2, gOut);
    analogWrite(bPin2, bOut);
}

// void receiveEvent(int howMany)
// {
//     x = Wire.read();   // receive byte as an integer
//     Serial.println(x); // print the integer
// }
