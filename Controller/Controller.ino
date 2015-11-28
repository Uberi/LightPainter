#include <math.h>
#include <Servo.h> 

#define SERVO1_PIN 9
#define SERVO2_PIN 10
#define SERVO3_PIN 11
#define RED_PIN 3
#define GREEN_PIN 5
#define BLUE_PIN 6

#define VERTICAL_ROD_LENGTH 205.0
#define HORIZONTAL_ROD_LENGTH 115.0

Servo servo1, servo2, servo3;

void setup()
{
  Serial.begin(9600);
  servo1.attach(SERVO1_PIN);
  servo2.attach(SERVO2_PIN);
  servo3.attach(SERVO3_PIN);
}

void set_color(char r, char g, char b)
{
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void do_spiral()
{
  double i = 0;
  const double amplitude = 20;
  for (double reference = 70; reference <= 130; reference += 0.04)
  {
    double signalA = sin(i + 0 * 2 * M_PI / 3), signalB = sin(i + 1 * 2 * M_PI / 3), signalC = sin(i + 2 * 2 * M_PI / 3);
    servo1.write(reference + amplitude * signalA);
    servo2.write(reference + amplitude * signalB);
    servo3.write(reference + amplitude * signalC);
    set_color(55 + (signalA + 1) / 2 * 200, 55 + (signalB + 1) / 2 * 200, 55 + (signalC + 1) / 2 * 200);
    i += 0.02;
    delay(5);
  }
}

void do_rings()
{
  const double amplitude = 20;
  for (double reference = 70; reference <= 130; reference += 15)
  {
    for (double i = 0; i < 2 * M_PI; i += 0.02)
    {
      double signalA = sin(i + 0 * 2 * M_PI / 3), signalB = sin(i + 1 * 2 * M_PI / 3), signalC = sin(i + 2 * 2 * M_PI / 3);
      servo1.write(reference + amplitude * signalA);
      servo2.write(reference + amplitude * signalB);
      servo3.write(reference + amplitude * signalC);
      if (reference <= 70) set_color(255, 0, 0);
      else if (reference <= 85) set_color(0, 255, 0);
      else if (reference <= 100) set_color(0, 0, 255);
      else if (reference <= 115) set_color(255, 255, 0);
      else if (reference <= 130) set_color(255, 0, 255);
      delay(5);
    }
    set_color(0, 0, 0);
    servo1.write(reference + amplitude * sin(0 * 2 * M_PI / 3));
    servo2.write(reference + amplitude * sin(1 * 2 * M_PI / 3));
    servo3.write(reference + amplitude * sin(2 * 2 * M_PI / 3));
    delay(100);
  }
}

void do_sparks()
{
  const double smallest = 70;
  const double largest = 130;
  for (int i = 0; i < 10; i ++)
  {
    servo1.write(random(smallest, largest));
    servo2.write(random(smallest, largest));
    servo3.write(random(smallest, largest));
    delay(100);
    double offset = random(0, 2 * M_PI * 100000) / 100000;
    double signalA = sin(offset + 0 * 2 * M_PI / 3), signalB = sin(offset + 1 * 2 * M_PI / 3), signalC = sin(offset + 2 * 2 * M_PI / 3);
    set_color(signalA * 255, signalB * 255, signalC * 255);
    delay(500);
  }
}

void do_flares()
{
  const double reference = 130;
  const double amplitude = 60;
  for (int i = 0; i < 10; i ++)
  {
    double offset = random(0, 2 * M_PI * 100000) / 100000;
    double signalA = sin(offset + 0 * 2 * M_PI / 3), signalB = sin(offset + 1 * 2 * M_PI / 3), signalC = sin(offset + 2 * 2 * M_PI / 3);
    set_color(signalA * 255, signalB * 255, signalC * 255);
    double growthA = random(amplitude), growthB = random(amplitude), growthC = random(amplitude);
    for (double i = 0; i <= 1; i += 0.01)
    {
      servo1.write(reference - i * growthA);
      servo2.write(reference - i * growthB);
      servo3.write(reference - i * growthC);
      delay(10);
    }
    set_color(0, 0, 0);
    delay(500);
  }
}

void loop()
{
  do_flares();
  set_color(0, 0, 0);
  delay(3000);
  do_sparks();
  set_color(0, 0, 0);
  delay(3000);
  do_rings();
  set_color(0, 0, 0);
  delay(3000);
  do_spiral();
  set_color(0, 0, 0);
  delay(3000);
  do_spiral();
  set_color(0, 0, 0);
  delay(3000);
}
