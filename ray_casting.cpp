#include <iostream>
#include "geo_headers/renderer.h"

typedef long long ll;

using namespace std;

enum LastLineStatus { hitBottom, hitTop, hitInside, hitStraight, none};

class RayCasting {
private:
  static LastLineStatus lastLineStatus;
  static long linesCrossed;

  RayCasting();
  RayCasting(const RayCasting&);

  bool checkCrossedLines(Line line1, Line line2);
  bool pointInsideLine(Point point, Line line);
  string getPointPosition(Point point, Polygon& polygon);
  void reset() {
    lastLineStatus = none;
    linesCrossed = 0;
  }
};

long RayCasting::linesCrossed = 0;
LastLineStatus RayCasting::lastLineStatus = none;

bool RayCasting::checkCrossedLines(Line line1, Line line2) {
  ll pos1  = orientationTest(line1, line2.getStartPoint()); // the position of the line2 start point compared to line1
  ll pos2 = orientationTest(line1, line2.getEndPoint()); // the position of the line2 end point compared to line1
  ll pos3 = orientationTest(line2, line1.getStartPoint()); // the position of the line1 start point compared to line2
  ll pos4 = orientationTest(line2, line1.getEndPoint()); // the position of the line1 end point compared to line2

  // if not crossed
  if (((pos1 > 0 && pos2 > 0) || (pos1 < 0 && pos2 < 0)) || ((pos3 > 0 && pos4 > 0) || (pos3 < 0 && pos4 < 0))) {
    return false;
  }

  // if the lines are collinear
  if (pos1 == 0 && pos2 == 0 && pos3 == 0 && pos4 == 0) {
    if (
      pointInsideLine(line1.getStartPoint(), line2) || 
      pointInsideLine(line1.getEndPoint(), line2) ||
      pointInsideLine(line2.getStartPoint(), line1) ||
      pointInsideLine(line2.getEndPoint(), line1)
    ) 
      return true;
    else 
      return false;
  }


  // Checking if the lines are intersecting only in one point
  // both points are left (top)
  if (pos3 >= 0 && pos4 >= 0) {
    // and the last line was touched only in one edge, but it was on the bottom
    if (lastLineStatus == hitBottom)
      linesCrossed += 1;
    
    lastLineStatus = hitTop;
    return true;
  } 
  // both points are right (bottom)
  else if (pos3 <= 0 && pos4 <= 0) {
    // and the last line was touched only in one edge, but it was on the top
    if (lastLineStatus == hitTop)
      linesCrossed += 1;

    lastLineStatus = hitBottom;
    return true;
  }

  // the lines are crossed one into another
  linesCrossed++;
  lastLineStatus = hitInside;
  return true;
}


bool RayCasting::pointInsideLine(Point point, Line line) {
  // if the points are not collinear then the point is not on the line
  if (orientationTest(line, point) != 0) return false;
  // but if they are collinear then we check if the point is on the line
  ll d1 = point.getX() - line.getStartPoint().getX();
  ll d2 = line.getEndPoint().getX() - point.getX();
  return d1*d2 >= 0;
}

string RayCasting::getPointPosition(Point point, Polygon& polygon) {
  Line extremeLine(point, Point(polygon.getRightExtreme() + 1, point.getY()));
  reset();
  Line line;
  for (ll i = 0; i < polygon.getSize(); i++) {
    if (i < polygon.getSize() - 1) 
      line = Line(polygon.getPoint(i), polygon.getPoint(i+1));
    else
      line = Line(polygon.getPoint(i), polygon.getPoint(0));

    // if it is equal to one of these points, then it is automatically on the edge of the polygon
    if (point == line.getStartPoint() || point == line.getEndPoint())
      return "BOUNDARY";

    //if these two lines intersect and the point is inside the line
    if (checkCrossedLines(line, extremeLine) && pointInsideLine(point, line))
      return "BOUNDARY";
  }

  if (this->linesCrossed % 2 == 0) return "OUTSIDE";
  else return "INSIDE";
}

int main() {

}