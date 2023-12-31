#include <iostream>
#include <fstream>
#include <map>
#include "geo_headers/renderer.h"

typedef long long ll;

using namespace std;

enum LastLineStatus { hitBottom, hitTop, hitInside, hitStraight, none};
enum PointPosition { INSIDE, OUTSIDE, BOUNDARY };
class RayCasting {
private:
  static LastLineStatus lastLineStatus;
  static long linesCrossed;

  RayCasting();
  RayCasting(const RayCasting&);

  static bool checkCrossedLines(Line line1, Line line2);
  static bool pointInsideLine(Point point, Line line);
  static void reset() {
    lastLineStatus = none;
    linesCrossed = 0;
  }
public:
  /**
   * @brief Determines the position of a point with respect to a polygon.
   * @param point The point to be tested.
   * @param polygon The polygon to be tested against.
   * @return The position of the point: INSIDE, OUTSIDE, or BOUNDARY.
   */
  static PointPosition getPointPosition(Point point, Polygon& polygon);
};

long RayCasting::linesCrossed = 0;
LastLineStatus RayCasting::lastLineStatus = none;

bool RayCasting::checkCrossedLines(Line line, Line extremeLine) {
  ll pos1  = orientationTest(line, extremeLine.getStartPoint()); // The position of the extremeLine start point compared to line
  ll pos2 = orientationTest(line, extremeLine.getEndPoint()); // The position of the extremeLine end point compared to line
  ll pos3 = orientationTest(extremeLine, line.getStartPoint()); // The position of the line start point compared to extremeLine
  ll pos4 = orientationTest(extremeLine, line.getEndPoint()); // The position of the line end point compared to extremeLine

  // If the lines do not cross
  if (((pos1 > 0 && pos2 > 0) || (pos1 < 0 && pos2 < 0)) || ((pos3 > 0 && pos4 > 0) || (pos3 < 0 && pos4 < 0)))
    return false;

  // If the lines are collinear, check if they intersect or touch at any point
  if (pos1 == 0 && pos2 == 0 && pos3 == 0 && pos4 == 0) {
    if (
      pointInsideLine(line.getStartPoint(), extremeLine) || 
      pointInsideLine(line.getEndPoint(), extremeLine) ||
      pointInsideLine(extremeLine.getStartPoint(), line) ||
      pointInsideLine(extremeLine.getEndPoint(), line)
    ) 
      return true;
    else 
      return false;
  }


  // Checking if the lines are intersecting only in one point
  // Both points are left (top)
  if (pos3 >= 0 && pos4 >= 0) {

    // And the last line was touched only in one edge, but it was on the bottom
    if (lastLineStatus == hitBottom)
      linesCrossed += 1;

    lastLineStatus = hitTop;
    return true;
  } 
  // Both points are right (bottom)
  else if (pos3 <= 0 && pos4 <= 0) {

    // And the last line was touched only in one edge, but it was on the top
    if (lastLineStatus == hitTop)
      linesCrossed += 1;

    lastLineStatus = hitBottom;
    return true;
  }

  // The lines are crossed one into another
  linesCrossed++;
  lastLineStatus = hitInside;
  return true;
}

bool RayCasting::pointInsideLine(Point point, Line line) {
  // If the points are not collinear then the point is not on the line
  if (orientationTest(line, point) != 0) return false;
  // But if they are collinear then we check if the point is on the line
  ll d1 = point.getX() - line.getStartPoint().getX();
  ll d2 = line.getEndPoint().getX() - point.getX();
  return d1*d2 >= 0;
}

PointPosition RayCasting::getPointPosition(Point point, Polygon& polygon) {
  polygon.checkLastPoint();
  Line extremeLine(point, Point(polygon.getRightExtreme() + 10, point.getY()));
  reset();
  Line line;
  for (ll i = 0; i < polygon.getSize(); i++) {
    if (i < polygon.getSize() - 1) 
      line = Line(polygon.getPoint(i), polygon.getPoint(i+1));
    else
      line = Line(polygon.getPoint(i), polygon.getPoint(0));

    // If it is equal to one of these points, then it is automatically on the edge of the polygon
    if (point == line.getStartPoint() || point == line.getEndPoint())
      return BOUNDARY;

    // If these two lines intersect and the point is inside the line
    if (checkCrossedLines(line, extremeLine) && pointInsideLine(point, line))
      return BOUNDARY;
  }

  if (linesCrossed % 2 == 0) return OUTSIDE;
  else return INSIDE;
}

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "Please pass the input and output files name!\n";
    return 0;
  }

  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  map<Point, PointPosition> pointPositions;
  
  Polygon polygon;
  fin >> polygon;
  
  int pointsCount;
  fin >> pointsCount;

  Point p;
  for (int i = 0; i < pointsCount; i++) {
    fin >> p;
    pointPositions[p] = RayCasting::getPointPosition(p, polygon);
    fout << p << ": " << ((pointPositions[p] == INSIDE) ? "INSIDE" : ((pointPositions[p] == OUTSIDE) ? "OUTSIDE" : "BOUNDARY") ) << endl;
  }

  Renderer renderer(800, 800, "Ray Casting");
  bool running = true;
  while (running) { 
    if (renderer.shouldQuit())
      running = false;
    
    renderer.clear();
    renderer.drawAxis();
    renderer.drawPolygon(polygon);

    // Render all points
    map<Point, PointPosition>::iterator it;
    for (it = pointPositions.begin(); it != pointPositions.end(); ++it) {
      Point point = it->first;
      switch (it->second){
        case INSIDE:
          renderer.drawPoint(point, 31, 145, 0); // green
          break;
        case OUTSIDE:
          renderer.drawPoint(point, 145, 0, 17); // red
          break;
        case BOUNDARY:
          renderer.drawPoint(point, 200, 130, 0); // yellow
          break;
        default:
          break;
      }
    }
    renderer.update();
  }
  fin.close();
  fout.close();
  return 0;
}