#include <iostream>

using namespace std;

struct Point {
  int x, y;
};

int Orientation(Point p1, Point p2, Point p3) {
  int val = (p2.y - p1.y) * (p3.x - p2.x) -
            (p3.y - p2.y) * (p2.x - p1.x);
  if (val == 0) {
    return 0;
  }
  return (val > 0) ? 1 : 2; // clock or counterclock
}

int main() {
  Point p1 = {0, 0}, p2 = {4, 4}, p3 = {1, 2};
  int o = Orientation(p1, p2, p3);
  if (o == 0) {
    cout << "Linear";
  } else if (o == 1) {
    cout << "Clockwise";
  } else {
    cout << "CounterClockwise";
  }
  return 0;
}
  
