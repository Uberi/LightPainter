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

void set_position(double x, double y, double z) {
  double plane_x, plane_y, plane_length, plane_angle, interior_angle;
  double px, py;
  
  // set servo 1
  px = 0, py = y;
  plane_length = sqrt(px * px + py * py + z * z);
  plane_x = sqrt(plane_length * plane_length - z * z); plane_y = z;
  plane_angle = acos(plane_x / plane_length);
  interior_angle = acos((plane_length * plane_length - VERTICAL_ROD_LENGTH * VERTICAL_ROD_LENGTH + HORIZONTAL_ROD_LENGTH * HORIZONTAL_ROD_LENGTH) / (2 * plane_length * HORIZONTAL_ROD_LENGTH));
  servo1.write((plane_angle - interior_angle) * 180 / M_PI + 90);
  Serial.println((plane_angle - interior_angle) * 180 / M_PI + 90);
  
  // set servo 2
  px = x - (x * -sqrt(3) / 2 + y * -1 / 2) * (-sqrt(3) / 2), py = y - (x * -sqrt(3) / 2 + y * -1 / 2) * (-1 / 2);
  plane_length = sqrt(px * px + py * py + z * z);
  plane_x = -sqrt(plane_length * plane_length - z * z); plane_y = z;
  plane_angle = acos(plane_x / plane_length);
  interior_angle = acos((plane_length * plane_length - VERTICAL_ROD_LENGTH * VERTICAL_ROD_LENGTH + HORIZONTAL_ROD_LENGTH * HORIZONTAL_ROD_LENGTH) / (2 * plane_length * HORIZONTAL_ROD_LENGTH));
  servo2.write((plane_angle - interior_angle) * 180 / M_PI + 90);
  Serial.println((plane_angle - interior_angle) * 180 / M_PI + 90);
  
  // set servo 3
  px = x - (x * -sqrt(3) / 2 + y * 1 / 2) * (-sqrt(3) / 2), py = y - (x * -sqrt(3) / 2 + y * 1 / 2) * (1 / 2);
  plane_length = sqrt(px * px + py * py + z * z);
  plane_x = sqrt(plane_length * plane_length - z * z); plane_y = z;
  plane_angle = acos(plane_x / plane_length);
  interior_angle = acos((plane_length * plane_length - VERTICAL_ROD_LENGTH * VERTICAL_ROD_LENGTH + HORIZONTAL_ROD_LENGTH * HORIZONTAL_ROD_LENGTH) / (2 * plane_length * HORIZONTAL_ROD_LENGTH));
  servo3.write((plane_angle - interior_angle) * 180 / M_PI + 90);
  Serial.println((plane_angle - interior_angle) * 180 / M_PI + 90);
  Serial.println();
}

void set_color(int r, int g, int b)
{
  analogWrite(RED_PIN, r);
  analogWrite(GREEN_PIN, g);
  analogWrite(BLUE_PIN, b);
}

void loop()
{
  delay(1000);
  double i;
  while (true)
  {
    i += 0.01;
    set_position(80 * sin(i), 80 * cos(i), 120);
    delay(10);
  }
}
