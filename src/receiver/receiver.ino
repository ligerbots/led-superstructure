#include <Wire.h>

int address = 4;

int rChannel = 0;
int gChannel = 0;
int bChannel = 0;

#define rPin 6
#define gPin 5
#define bPin 3

#define rPin2 11
#define gPin2 10
#define bPin2 9

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
      x = incomingByte - 48;
      // say what you got:
      Serial.print("I received: ");
      Serial.println(incomingByte, DEC);
    }
    modeSelect(x);
}

void modeSelect(int select) {
    switch (select)
    {
        default:
            colorSelector(0);
            outputToLED(rChannel, gChannel, bChannel);
            break;
        // Purple Static Light 
        case 1:
            colorSelector(1);
            outputToLED(rChannel, gChannel, bChannel);
            break;
        // Yellow Static LightMode
        case 2:
            colorSelector(2);
            outputToLED(rChannel, gChannel, bChannel);
            break;
        // Orange Static Light
        case 3:
            colorSelector(3);
            outputToLED(rChannel, gChannel, bChannel);
            break;
        // Orange Pulse
        case 4:
            orangePulse();
            break; 
    }
}
void colorSelector(int select) {
    switch (select)
    {
        // check for off mode
    case 0:
        rChannel = 0;
        gChannel = 0;
        bChannel = 0;
        // Serial.println("Default");
        break;

        // check for purple mode
    case 1:
        rChannel = 194;
        gChannel = 0;
        bChannel = 242;
        Serial.println("Purple");
        break;

        // Check for yellow mode
    case 2:
        rChannel = 255;
        gChannel = 120;
        bChannel = 0;
        Serial.println("Yellow");
        break;

        // check for orange mode
    case 3:
        rChannel = 255;
        gChannel = 55;
        bChannel = 0;
        Serial.println("Orange");
        break;
        // Red
    case 4:
        rChannel = 255;
        gChannel = 0;
        bChannel = 0;
        Serial.println("Red");
        break;
    case 5:
        rChannel = 0;
        gChannel = 255;
        bChannel = 0;
        Serial.println("Green");
        break;
    case 6:
        rChannel = 0;
        gChannel = 0;
        bChannel = 255;
        Serial.println("Blue");
        break;
    case 7:
        orangePulse();
        // set default as Off
    
    default:
        rChannel = 0;
        gChannel = 0;
        bChannel = 0;
        break;
    }
}

void outputToLED(int rValue, int gValue, int bValue){
    analogWrite(rPin, rValue);
    analogWrite(gPin, gValue);
    analogWrite(bPin, bValue);
    analogWrite(rPin2, rValue);
    analogWrite(gPin2, gValue);
    analogWrite(bPin2, bValue);
}

void orangePulse(){
    Serial.println("Orange Pulse");
    colorSelector(3);
    int maxDecrease = 50;
    int delayTime = 7;
    for (int i = 0; i < maxDecrease; i++)
    {
        int decreasedRChannel = rChannel - i;
        int decreasedGChannel = gChannel - i;
        int decreasedBChannel = bChannel - i;

        if (decreasedRChannel < 0)
        {
            decreasedRChannel = 0;
        }
        if (decreasedGChannel < 0)
        {
            decreasedGChannel = 0;
        }
        if (decreasedBChannel < 0)
        {
            decreasedBChannel = 0;
        }

        outputToLED(decreasedRChannel, decreasedGChannel, decreasedBChannel);
        delay(delayTime);
    }
    for (int i = maxDecrease; i > 0; i--)
    {
        int increasedRChannel = rChannel - i;
        int increasedGChannel = gChannel - i;
        int increasedBChannel = bChannel;

        outputToLED(increasedRChannel, increasedGChannel, increasedBChannel);
        delay(delayTime);
    }
}

// void receiveEvent(int howMany)
// {
//     x = Wire.read();   // receive byte as an integer
//     Serial.println(x); // print the integer
// }