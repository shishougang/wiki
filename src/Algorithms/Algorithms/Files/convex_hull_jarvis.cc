#include <iostream>
#include <vector>

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

void ConvexHull(Point *points, int n) {
  if (n < 3) {
    return;
  }
  vector<Point> hull;
  // Find the leftmost point
  int l = 0;
  for (int i = 1; i < n; ++i) {
    if (points[i].x < points[l].x) {
      l = i;
    }
  }
  // Start from leftmost point, keep moving counterclockwise
  // until reach the start point again.
  int p = l, q;
  do {
    hull.push_back(points[p]);
    // Search for a point 'q' such that orientation(p, q, i)
    // is counterclockwise for any other point i.
    q = (p + 1) % n;
    for (int i = 0; i < n; ++i) {
      // If i is more counterclockwise than current q
      if (Orientation(points[p], points[i], points[q]) == 2) {
        q = i;
      }
    }
    p = q;
  } while (p != l);
  for (int i = 0; i < hull.size(); ++i) {
    cout << "(" << hull[i].x << ", "
         << hull[i].y << ")\n";
  }
}

int main() {
  Point points[] = {{0, 3}, {2, 2}, {1, 1}, {2, 1},
                    {3, 0}, {0, 0}, {3, 3}};
  int n = sizeof(points)/sizeof(points[0]);
  ConvexHull(points, n);
  return 0;
}

