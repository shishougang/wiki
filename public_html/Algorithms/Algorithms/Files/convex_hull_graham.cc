#include <cstdlib>
#include <iostream>
#include <stack>

using namespace std;

struct Point {
  int x, y;
};

// A globle point needed for sorting points with the first point
Point p0;

// 0: colinear
// 1: clockwise
// 2: counterclockwise
int Orientation(Point p1, Point p2, Point p3) {
  int val = (p2.y - p1.y) * (p3.x - p2.x) -
            (p3.y - p2.y) * (p2.x - p1.x);
  if (val == 0) {
    return 0;
  }
  return (val > 0) ? 1 : 2; // clock or counterclock
}

Point NextToTop(stack<Point> *stk) {
  Point p = stk->top();
  stk->pop();
  Point next = stk->top();
  stk->push(p);
  return next;
}

int Swap(Point *p1, Point *p2) {
  Point temp = *p1;
  *p1 = *p2;
  *p2 = temp;
}

// square distance between p1 and p2;
int DistSqure(const Point &p1, const Point &p2) {
  return (p1.x - p2.x) * (p1.x - p2.x) +
      (p1.y - p2.y) * (p1.y - p2.y);
}

int Compare(const void *vp1, const void *vp2) {
  Point *p1 = (Point *) vp1;
  Point *p2 = (Point *) vp2;
  int o = Orientation(p0, *p1, *p2);
  if (o == 0) {
    return (DistSqure(p0, *p2) >= DistSqure(p0, *p1)) ? -1 : 1;
  }
  return (o == 2) ? -1 : 1;
}

void ConvexHull(Point *points, int n) {
  // Find the bottommost point
  int ymin = points[0].y;
  int min = 0;
  for (int i = 1; i < n; ++i) {
    int y = points[i].y;
    if ((y < ymin) || (y == ymin &&
                       points[i].x < points[min].x)) {
      ymin = points[i].y;
      min = i;
    }
  }
  // Place the bottom-most point at first position
  Swap(&points[0], &points[min]);
  p0 = points[0];
  qsort(&points[1], n - 1, sizeof(Point), Compare);
  // If two or more points make same angle with p0,
  // Remove all but the one that is farthest from p0
  int m = 1;
  for (int i = 1; i < n; ++i) {
    while (i < n - 1 && Orientation(p0, points[i],
                                    points[i+1]) == 0) {
      ++i;
    }
    points[m++] = points[i];
  }
  if (m < 3) {
    return;
  }
  stack<Point> stk;
  stk.push(points[0]);
  stk.push(points[1]);
  stk.push(points[2]);
  for (int i = 3; i < m; ++i) {
    while (Orientation(NextToTop(&stk), stk.top(), points[i]) != 2) {
      stk.pop();
    }
    stk.push(points[i]);
  }
  while (!stk.empty()) {
    Point p = stk.top();
    stk.pop();
    cout << "(" << p.x << ", " << p.y <<")" << endl;
  }
}

int main() {
  Point points[] = {{0, 3}, {1, 1}, {2, 2}, {4, 4},
                    {0, 0}, {1, 2}, {3, 1}, {3, 3}};
  int n = sizeof(points)/sizeof(points[0]);
  ConvexHull(points, n);
  return 0;
}
