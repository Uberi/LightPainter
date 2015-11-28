#include <math.h>
#include <iostream>

using namespace std;

#define VERTICAL_ROD_LENGTH 205.0
#define HORIZONTAL_ROD_LENGTH 115.0

void set_position(double x, double y, double z) {
  double plane_x, plane_y, plane_length, plane_angle, interior_angle;
  double px, py;
  
  // set servo 1
  px = 0, py = y;
  plane_length = sqrt(px * px + py * py + z * z);
  plane_x = sqrt(plane_length * plane_length - z * z); plane_y = z;
  plane_angle = acos(plane_x / plane_length);
  interior_angle = acos((plane_length * plane_length - VERTICAL_ROD_LENGTH * VERTICAL_ROD_LENGTH + HORIZONTAL_ROD_LENGTH * HORIZONTAL_ROD_LENGTH) / (2 * plane_length * HORIZONTAL_ROD_LENGTH));
  cout << ((plane_angle - interior_angle) * 180 / M_PI + 90) << endl;
  
  // set servo 2
  px = x - (x * -sqrt(3) / 2 + y * -1 / 2) * (-sqrt(3) / 2), py = y - (x * -sqrt(3) / 2 + y * -1 / 2) * (-1 / 2);
  plane_length = sqrt(px * px + py * py + z * z);
  plane_x = -sqrt(plane_length * plane_length - z * z); plane_y = z;
  plane_angle = acos(plane_x / plane_length);
  interior_angle = acos((plane_length * plane_length - VERTICAL_ROD_LENGTH * VERTICAL_ROD_LENGTH + HORIZONTAL_ROD_LENGTH * HORIZONTAL_ROD_LENGTH) / (2 * plane_length * HORIZONTAL_ROD_LENGTH));
  cout << ((plane_angle - interior_angle) * 180 / M_PI + 90) << endl;
  
  // set servo 3
  px = x - (x * -sqrt(3) / 2 + y * 1 / 2) * (-sqrt(3) / 2), py = y - (x * -sqrt(3) / 2 + y * 1 / 2) * (1 / 2);
  plane_length = sqrt(px * px + py * py + z * z);
  plane_x = sqrt(plane_length * plane_length - z * z); plane_y = z;
  plane_angle = acos(plane_x / plane_length);
  interior_angle = acos((plane_length * plane_length - VERTICAL_ROD_LENGTH * VERTICAL_ROD_LENGTH + HORIZONTAL_ROD_LENGTH * HORIZONTAL_ROD_LENGTH) / (2 * plane_length * HORIZONTAL_ROD_LENGTH));
  cout << ((plane_angle - interior_angle) * 180 / M_PI + 90) << endl << endl;
}

int main()
{
  set_position(50, 0, 120);
  set_position(0, 50, 120);
  set_position(-50, 0, 120);
  set_position(0, -50, 120);
}
