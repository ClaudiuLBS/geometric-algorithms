#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "geometric_basics.h"

using namespace std;

class Renderer {
private:
  const char* WINDOW_NAME;
  const int SCREEN_WIDTH;
  const int SCREEN_HEIGHT;
  SDL_Renderer* renderer;
  SDL_Window* window;
  SDL_Event event;
  float scale;
public:
  Renderer(int screenWidth, int screenHeight, const char* windowName): SCREEN_WIDTH(screenWidth), SCREEN_HEIGHT(screenHeight), WINDOW_NAME(windowName) {
    SDL_Init(SDL_INIT_EVERYTHING);
    scale = 100;
    window = SDL_CreateWindow( WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
  }

  bool shouldQuit();
  bool hasEvents();

  int normalizeX(int x);
  int normalizeY(int y);

  void clear();
  void update();
  void drawAxis();
  void drawPoint(Point point, int, int, int);
  void drawPoint(int x, int y, int, int, int);
  void drawLine(Line line, int, int, int);
  void drawPolygon(Polygon polygon, int, int, int);

  ~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
};

int Renderer::normalizeX(int x) {
  // recalculate the scale
  float maxX = SCREEN_WIDTH / 3;
  scale = min(scale, abs((float)maxX / x));
  
  // return normalized x
  return SCREEN_WIDTH / 2 + scale * x;
}

int Renderer::normalizeY(int y) {
  // recalculate the scale
  float maxY = SCREEN_HEIGHT / 3;
  scale = min(scale, abs((float)maxY / y));
  
  // return normalized y
  return SCREEN_HEIGHT / 2 - scale * y;
}

bool Renderer::shouldQuit() {
  return hasEvents() && event.type == SDL_QUIT;
}

bool Renderer::hasEvents() {
  return SDL_PollEvent(&event) != 0;
}

void Renderer::clear() {
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);
}

void Renderer::update() {
  SDL_RenderPresent(renderer);
}

void Renderer::drawAxis() {
  SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
  SDL_RenderDrawLine(renderer, 10, SCREEN_HEIGHT / 2, SCREEN_WIDTH - 10, SCREEN_HEIGHT / 2);
  SDL_RenderDrawLine(renderer, SCREEN_WIDTH / 2, 10, SCREEN_WIDTH / 2, SCREEN_HEIGHT - 10);
}
void Renderer::drawPoint(int x, int y, int r = 22, int g = 14, int b = 237) { 
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  x = normalizeX(x);
  y = normalizeY(y);
  SDL_RenderDrawPoint(renderer, x, y);
  // draw X
  SDL_RenderDrawLine(renderer, x - 2, y - 2, x + 2, y + 2);
  SDL_RenderDrawLine(renderer, x + 2, y - 2, x - 2, y + 2);
}

void Renderer::drawPoint(Point point, int r = 22, int g = 14, int b = 237) {
  drawPoint(point.getX(), point.getY(), r, g, b);
}

void Renderer::drawLine(Line line, int r = 181, int g = 14, int b = 237) {
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);
  SDL_RenderDrawLine(renderer, 
    normalizeX(line.getStartPoint().getX()), normalizeY(line.getStartPoint().getY()), 
    normalizeX(line.getEndPoint().getX()), normalizeY(line.getEndPoint().getY())
  );
}

void Renderer::drawPolygon(Polygon polygon, int r = 10, int g = 100, int b = 10) {
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);

  int numPoints = polygon.getSize();
  SDL_Point* points = new SDL_Point[numPoints];
  for (int i = 0; i < numPoints; i++) {
    Point p = polygon.getPoint(i);
    points[i].x = normalizeX(p.getX());
    points[i].y = normalizeY(p.getY());
  }
  SDL_RenderDrawLines(renderer, points, numPoints);
  SDL_RenderDrawLine(renderer, points[numPoints - 1].x, points[numPoints - 1].y, points[0].x, points[0].y);
  delete[] points;
}

#endif