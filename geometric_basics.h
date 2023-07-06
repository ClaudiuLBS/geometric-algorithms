#ifndef GEOMETRIC_BASICS_H
#define GEOMETRIC_BASICS_H

#include <iostream>
#include <vector>

typedef long long ll;

using namespace std;

class Point;
class Line;
class Polygon;

ll orientationTest(Point p1, Point p2, Point p3);
ll orientationTest(Line line, Point point);


// ============ POINT ============
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
  Point& operator=(const Point& point);
  friend ostream& operator<<(ostream& out, Point point);
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
Point& Point::operator=(const Point& point) {
  x = point.x;
  y = point.y;
  return *this;
}
ostream& operator<<(ostream& out, Point point) {
  out << "(" << point.x << ", " << point.y << ")";
  return out;
}


// ============ LINE ============
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
}

ostream& operator<<(ostream& out, Line line) {
  out << line.startPoint << " -> " << line.endPoint;
  return out;
}


// ============ POLYGON ============
class Polygon {
private:
  vector<Point> points;
  ll rightExtreme;
  ll leftExtreme;
  ll topExtreme;
  ll bottomExtreme;
public:
  Polygon();
  Polygon(vector<Point> points);
  void addPoint(Point& newPoint);
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


// FUNCTIONS
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
  return (
    point.getX() * line.getStartPoint().getY() + 
    line.getStartPoint().getX() * line.getEndPoint().getY() - 
    point.getX() * line.getEndPoint().getY() - 
    line.getStartPoint().getX() * point.getY() + 
    line.getEndPoint().getX() * point.getY() - 
    line.getEndPoint().getX() * line.getStartPoint().getY()
  );
}


#endif