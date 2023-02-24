#include <Wire.h>
#include <stdio.h>

int i2cAddress = 4;

#define rPin 6
#define gPin 5
#define bPin 3

#define rPin2 11
#define gPin2 10
#define bPin2 9

struct color
{
    int red;
    int green;
    int blue;
};

int x = 4;

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
    Wire.onReceive(modeUpdate);
    // Wire.onRequest(modeUpdate); // register event
    Serial.begin(115200);
}

void modeUpdate()
{
    while (Wire.available())
    {
        x = Wire.read();
        Serial.println(x);
    }
    modeSelect(x);
}

void loop()
{
    modeSelect(x);
}

void modeSelect(int select)
{
    color c = {0, 0, 0};
    switch (select)
    {
    // No Color
    default:
        c = colorSelector(0);
        outputToLED(c);
        Serial.println("No Color");
        break;
    // Purple Static Light
    case 1:
        c = colorSelector(1);
        outputToLED(c);
        Serial.println("Purple Static");
        break;
    // Yellow Static LightMode
    case 2:
        c = colorSelector(2);
        outputToLED(c);
        Serial.println("Yellow Static");
        break;
    // Orange Static Light
    case 3:
        c = colorSelector(3);
        outputToLED(c);
        Serial.println("Orange Static");
        break;
    // Orange Pulse
    case 4:
        heartBeatOrange();
        Serial.println("Orange Pulse");
        break;
    }
}
color colorSelector(int select)
{
    color c = {0, 0, 0};
    switch (select)
    {
    // Purple
    case 1:
        // Serial.println("Purple Static");
        c = {194, 0, 242};
        break;
    // Yellow
    case 2:
        // Serial.println("Yellow Static");
        c = {255, 150, 0};
        break;
    // Orange
    case 3:
        // Serial.println("Orange Static");
        c = {255, 55, 0};
        break;
    // Green
    case 4:
        // Serial.println("Green Static");
        c = {0, 255, 0};
        break;
    default:
        // Serial.println("No Color");
        c = {0, 0, 0};
        break;
    }
    return c;
}

void outputToLED(color c)
{
    analogWrite(rPin, c.red);
    analogWrite(gPin, c.green);
    analogWrite(bPin, c.blue);
    analogWrite(rPin2, c.red);
    analogWrite(gPin2, c.green);
    analogWrite(bPin2, c.blue);
}

void heartBeat(color c, int channels[3], int delayTime = 25, int decrement = 150)
{
    Serial.println("Pulse");
    color pulsedColor = c;
    int i = 0;
    while (true)
    {
        if (x != 4)
        {
            break;
        }
        outputToLED(pulsedColor);
        Serial.print("Pulse: ");
        Serial.print("(");
        Serial.print(pulsedColor.red);
        Serial.print(",");
        Serial.print(pulsedColor.green);
        Serial.print(",");
        Serial.print(pulsedColor.blue);
        Serial.println(")");
        delay(delayTime);
        if (pulsedColor.red > 0 && channels[0] == 1)
        {
            pulsedColor.red--;
        }
        if (pulsedColor.green > 0 && channels[1] == 1)
        {
            pulsedColor.green--;
        }
        if (pulsedColor.blue > 0 && channels[2] == 1)
        {
            pulsedColor.blue--;
        }
        if ((pulsedColor.red == 0 && channels[0]) || (pulsedColor.green == 0 && channels[1]) || (pulsedColor.blue == 0 && channels[2]))
        {
            break;
        }
        i++;
        if (i > decrement)
        {
            break;
        }
    }
    delay(10);
    i = 0;
    while (true)
    {
        if (x != 4)
        {
            break;
        }
        outputToLED(pulsedColor);
        Serial.print("Pulse: ");
        Serial.print("(");
        Serial.print(pulsedColor.red);
        Serial.print(",");
        Serial.print(pulsedColor.green);
        Serial.print(",");
        Serial.print(pulsedColor.blue);
        Serial.println(")");
        delay(delayTime);
        if (pulsedColor.red < c.red && channels[0] == 1)
        {
            pulsedColor.red++;
        }
        if (pulsedColor.green < c.green && channels[1] == 1)
        {
            pulsedColor.green++;
        }
        if (pulsedColor.blue < c.blue && channels[2] == 1)
        {
            pulsedColor.blue++;
        }
        if ((pulsedColor.red == c.red && channels[0]) || (pulsedColor.green == c.green && channels[1]) || (pulsedColor.blue == c.blue && channels[2]))
        {
            break;
        }
        i++;
        if (i > decrement)
        {
            break;
        }
    }
    Serial.println("Pulse End");
}

void pulse(color c, int pulses = 3, int pulseLength = 100, int pulseDelay = 100)
{
    for (int i = 0; i < pulses; i++)
    {
        outputToLED(c);
        delay(pulseLength);
        outputToLED(colorSelector(0));
        delay(pulseDelay);
    }
}

void heartBeatOrange()
{
    int channels[3] = {1, 1, 0};
    heartBeat(colorSelector(3), channels, 10);
}

void heartBeatPurple()
{
    int channels[3] = {1, 0, 1};
    heartBeat(colorSelector(1), channels, 10);
}

void pulseOrange()
{
    pulse(colorSelector(3));
}

void pulsePurple()
{
    pulse(colorSelector(1));
}

void pulseYellow()
{
    pulse(colorSelector(2));
}

void pulseGreen()
{
    pulse(colorSelector(4));
}