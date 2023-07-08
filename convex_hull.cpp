#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include "geo_headers/renderer.h"

typedef long long ll;

using namespace std;

int main(int argc, char* argv[]) {
  if (argc < 3) {
    cout << "Please pass the input and output files name!\n";
    return 0;
  }

  ifstream fin(argv[1]);
  ofstream fout(argv[2]);

  vector<Point> points;
  Point p;
  
  while (fin>>p) {
    points.push_back(p);
  }
  sort(points.begin(), points.end());

  

  Polygon convexHullInferior;
  convexHullInferior.addPoint(points[0]);
  convexHullInferior.addPoint(points[1]);
  for (int i = 2; i < points.size(); i++) {
    Point p1 = convexHullInferior.getPoint(convexHullInferior.getSize() - 2);
    Point p2 = convexHullInferior.getPoint(convexHullInferior.getSize() - 1);
    Point p3 = points[i];
    while (orientationTest(p1,p2,p3) <= 0 && convexHullInferior.getSize() >= 2) {
      convexHullInferior.removeLastPoint();
      p1 = convexHullInferior.getPoint(convexHullInferior.getSize() - 2);
      p2 = convexHullInferior.getPoint(convexHullInferior.getSize() - 1);  
    }
    convexHullInferior.addPoint(p3);
  }

  Polygon convexHullSuperior;
  convexHullSuperior.addPoint(points[points.size() - 1]);
  convexHullSuperior.addPoint(points[points.size() - 2]);
  for (int i = points.size() - 3; i >= 0; i--) {
    Point p1 = convexHullSuperior.getPoint(convexHullSuperior.getSize() - 2);
    Point p2 = convexHullSuperior.getPoint(convexHullSuperior.getSize() - 1);
    Point p3 = points[i];
    while (orientationTest(p1,p2,p3) <= 0 && convexHullSuperior.getSize() >= 2) {
      convexHullSuperior.removeLastPoint();
      p1 = convexHullSuperior.getPoint(convexHullSuperior.getSize() - 2);
      p2 = convexHullSuperior.getPoint(convexHullSuperior.getSize() - 1);  
    }
    convexHullSuperior.addPoint(p3);
  }
  
  for (int i = 0; i < convexHullInferior.getSize(); i++)
    fout << convexHullInferior.getPoint(i) << endl;
  for (int i = 0; i < convexHullSuperior.getSize(); i++)
    fout << convexHullSuperior.getPoint(i) << endl;

  Renderer renderer(800, 800, "Convex Hull");
  bool running = true;
  while (running) { 
    if (renderer.shouldQuit())
      running = false;
    
    renderer.clear();
    renderer.drawAxis();

    // draw all points
    for (auto p : points)
      renderer.drawPoint(p);

    //draw convex hull polygon 
    renderer.drawPolygon(convexHullInferior, 192, 17, 250, false);
    for (int i = 0; i < convexHullInferior.getSize(); i++)
      renderer.drawPoint(convexHullInferior.getPoint(i), 150, 0, 0);

    renderer.drawPolygon(convexHullSuperior, 49, 8, 138, false);
    for (int i = 0; i < convexHullSuperior.getSize(); i++)
      renderer.drawPoint(convexHullSuperior.getPoint(i), 150, 0, 0);

    renderer.update();
  }
  fin.close();
  fout.close();
  
}