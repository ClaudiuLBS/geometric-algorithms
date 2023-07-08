#ifndef GEOMETRIC_BASICS_H
#define GEOMETRIC_BASICS_H

#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

class Point;
class Line;
class Polygon;

/**
 * @brief Performs the orientation test for three points in a 2D space.
 *
 * The orientation test determines whether three points are clockwise, counterclockwise, or collinear.
 *
 * @param p1 The first point.
 * @param p2 The second point.
 * @param p3 The third point.
 * @return A value indicating the orientation:
 *         - Positive value: Points p1, p2, p3 are in counterclockwise order.
 *         - Negative value: Points p1, p2, p3 are in clockwise order.
 *         - Zero value: Points p1, p2, p3 are collinear.
 */
ll orientationTest(Point p1, Point p2, Point p3);

/**
 * @brief Performs the orientation test for a line segment and a point in a 2D space.
 *
 * The orientation test determines whether the point is to the left, right, or collinear with the line segment.
 *
 * @param line The line segment.
 * @param point The point to test.
 * @return A value indicating the orientation:
 *         - Positive value: The point is to the left of the line segment.
 *         - Negative value: The point is to the right of the line segment.
 *         - Zero value: The point is collinear with the line segment.
 */
ll orientationTest(Line line, Point point);

/**
 * @brief Represents a 2D point with x and y coordinates.
 */
class Point {
private:
  ll x;
  ll y;
public:
  Point();
  Point(ll x, ll y);

  void setPoint(ll x, ll y);
  void setX(ll x);
  void setY(ll y);

  ll getX();
  ll getY();

  bool operator==(const Point& point);
  bool operator<(const Point& point) const;
  Point& operator=(const Point& point);
  friend ostream& operator<<(ostream& out, Point point);
  friend istream& operator>>(istream& in, Point& point);
};

void Point::setPoint(ll x, ll y) {
  this->x = x;
  this->y = y;
}

Point::Point() {
  setPoint(0, 0);
}
Point::Point(ll x, ll y) {
  setPoint(x, y);
}

void Point::setX(ll x) { 
  this->x = x; 
}
void Point::setY(ll y) { 
  this->y = y; 
}

ll Point::getX() { return x; }
ll Point::getY() { return y; }

bool Point::operator==(const Point& point) {
  return x == point.x && y == point.y;
}
bool Point::operator<(const Point& point) const{
  // sorted by x, and if x are equal, sorted by y
  if (x == point.x)
    return y < point.y;
  else
    return x < point.x;
}
Point& Point::operator=(const Point& point) {
  x = point.x;
  y = point.y;
  return *this;
}
ostream& operator<<(ostream& out, Point point) {
  out << "(" << point.x << ", " << point.y << ")";
  return out;
}
istream& operator>>(istream& in, Point& point) {
  in >> point.x >> point.y;
  return in;
}


/**
 * @brief Represents a line segment defined by two points in a 2D space.
 */
class Line {
private:
  Point startPoint;
  Point endPoint;
public:
  Line();
  Line(Point startPoint, Point endPoint);
  Line(ll startPointX, ll startPointY, ll endPointX, ll endPointY);

  Point getStartPoint();
  Point getEndPoint();

  void setStartPoint(ll x, ll y);
  void setStartPoint(Point point);

  void setEndPoint(ll x, ll y);
  void setEndPoint(Point point);

  bool operator==(const Line& line);
  Line& operator=(const Line& line);
  friend ostream& operator<<(ostream& out, Line line);
};

Line::Line() { 
  startPoint = Point();
  endPoint = Point();
}
Line::Line(Point startPoint, Point endPoint) {
  this->startPoint = startPoint,
  this->endPoint = endPoint;
}
Line::Line(ll startPointX, ll startPointY, ll endPointX, ll endPointY) {
  startPoint = Point(startPointX, startPointY);
  endPoint = Point(endPointX, endPointY);
}

Point Line::getStartPoint() {
  return startPoint;
}
Point Line::getEndPoint() {
  return endPoint;
}

void Line::setStartPoint(ll x, ll y) {
  startPoint.setPoint(x, y);
}
void Line::setStartPoint(Point point) {
  startPoint = point;
}

void Line::setEndPoint(ll x, ll y) {
  endPoint.setPoint(x, y);
}
void Line::setEndPoint(Point point) {
  endPoint = point;
}

bool Line::operator==(const Line& line) {
  return startPoint == line.startPoint && endPoint == line.endPoint;
}
Line& Line::operator=(const Line& line) {
  setStartPoint(line.startPoint);
  setEndPoint(line.endPoint);
  return *this;
}

ostream& operator<<(ostream& out, Line line) {
  out << line.startPoint << " -> " << line.endPoint;
  return out;
}


/**
 * @brief Represents a polygon defined by a collection of points in a 2D space.
 */
class Polygon {
private:
  vector<Point> points; /**< The points that define the polygon. */
  ll rightExtreme; /**< The x-coordinate of the rightmost point in the polygon. */
  ll leftExtreme; /**< The x-coordinate of the leftmost point in the polygon. */
  ll topExtreme; /**< The y-coordinate of the topmost point in the polygon. */
  ll bottomExtreme; /**< The y-coordinate of the bottommost point in the polygon. */
public:
  Polygon();
  Polygon(vector<Point> points);

  /**
   * @param index The index of the point to retrieve.
   * @return The point at the specified index.
   */
  Point getPoint(int index);

  /**
   * @brief Removes the last point from the polygon.
   */
  void removeLastPoint();

  /**
   * @return The number of points in the polygon.
   */
  int getSize();

  /**
   * @brief Adds a new point to the polygon and updates the extreme coordinates.
   * @note The new point is collinear with the previous and last points, it is discarded to maintain a non-self-intersecting polygon.
   * @param newPoint The new point to be added to the polygon.
   */
  void addPoint(Point& newPoint);

  /**
   * @brief Checks and removes the last point of the polygon if it is collinear with the previous and first points.
   */
  void checkLastPoint();

  /**
   * @brief Reads the polygon data from an input stream.
   * @param in The input stream to read the polygon data from.
   */
  void read(istream& in);

  /**
   * @brief Getter for the rightmost x-coordinate of the polygon.
   * @return The rightmost x-coordinate of the polygon.
   */
  ll getRightExtreme() { return rightExtreme; }

  /**
   * @brief Getter for the leftmost x-coordinate of the polygon.
   * @return The leftmost x-coordinate of the polygon.
   */
  ll getLeftExtreme() { return leftExtreme; }

  /**
   * @brief Getter for the topmost y-coordinate of the polygon.
   * @return The topmost y-coordinate of the polygon.
   */
  ll getTopExtreme() { return topExtreme; }

   /**
   * @brief Getter for the bottommost y-coordinate of the polygon.
   * @return The bottommost y-coordinate of the polygon.
   */
  ll getBottomExtreme() { return bottomExtreme; }

  friend istream& operator>>(istream& in, Polygon& polygon);
};

Polygon::Polygon() {
  rightExtreme = 0;
  leftExtreme = 0;
  topExtreme = 0;
  bottomExtreme = 0;
}
Polygon::Polygon(vector<Point> points) {
  for (auto point : points) 
    addPoint(point);
}

void Polygon::addPoint(Point& newPoint) {
  if (points.size() < 2) {
    points.push_back(newPoint);
    return;
  }

  Point p1 = points[points.size() - 2];
  Point p2 = points[points.size() - 1];

  // check for collinear points
  if (orientationTest(p1, p2, newPoint) == 0)
    points.pop_back();
  points.push_back(newPoint);    

  rightExtreme = max(rightExtreme, newPoint.getX());
  leftExtreme = min(leftExtreme, newPoint.getX());
  topExtreme = max(topExtreme, newPoint.getY());
  bottomExtreme = min(bottomExtreme, newPoint.getY());
}

Point Polygon::getPoint(int index) {
  return points[index];
}

int Polygon::getSize() {
  return points.size();
}

void Polygon::removeLastPoint() {
  points.pop_back();
}

void Polygon::checkLastPoint() {
  Point p1 = points[points.size() - 2];
  Point p2 = points[points.size() - 1];
  Point p3 = points[0];
  if (orientationTest(p1, p2, p3) == 0)
    points.pop_back();
}

void Polygon::read(istream& in) {
  int pointsCount;
  Point p;
  for (in >> pointsCount; pointsCount > 0; pointsCount--) {
    in >> p;
    addPoint(p);
  }
}
istream& operator>>(istream& in, Polygon& polygon) {
  polygon.read(in);
  return in;
}


ll orientationTest(Point p1, Point p2, Point p3) {
  return (
    p3.getX() * p1.getY() + 
    p1.getX() * p2.getY() - 
    p3.getX() * p2.getY() - 
    p1.getX() * p3.getY() + 
    p2.getX() * p3.getY() - 
    p2.getX() * p1.getY()
  );
}

ll orientationTest(Line line, Point point) {
  return orientationTest(line.getStartPoint(), line.getEndPoint(), point);
}


#endif