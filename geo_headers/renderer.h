#ifndef RENDERER_H
#define RENDERER_H

#include <iostream>
#include <vector>
#include <SDL2/SDL.h>
#include "geometric_basics.h"

using namespace std;

/**
 * @brief The Renderer class provides functionality for rendering graphics using SDL library.
 */
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
    scale = 10000;
    window = SDL_CreateWindow( WINDOW_NAME, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, 0);
  }

  /**
   * @brief Checks if the application should quit.
   */
  bool shouldQuit();

  /**
   * @brief Checks if there are any pending events.
   */
  bool hasEvents();

  /**
   * @brief Normalizes the x-coordinate based on the screen width.
   * @param x The x-coordinate to normalize.
   * @return The normalized x-coordinate.
   *
   * @note This function recalculates the scale factor based on the screen width and the given x-coordinate.
   */
  int normalizeX(int x);

  /**
   * @brief Normalizes the y-coordinate based on the screen height.
   * @param y The y-coordinate to normalize.
   * @return The normalized y-coordinate.
   *
   * @note This function recalculates the scale factor based on the screen height and the given y-coordinate.
   */
  int normalizeY(int y);

  /**
   * @brief Clears the renderer.
   */
  void clear();

  /**
   * @brief Updates the screen with the rendered content.
   */
  void update();
  
  /**
   * @brief Draws the coordinate axis on the screen.
   */
  void drawAxis();

  /**
   * @brief Draws a point on the screen using the specified coordinates.
   * @param x The x-coordinate of the point.
   * @param y The y-coordinate of the point.
   * @param r The red component of the color (optional, default: 22).
   * @param g The green component of the color (optional, default: 14).
   * @param b The blue component of the color (optional, default: 237).
   */
  void drawPoint(Point point, int, int, int);

  /**
   * @brief Draws a point on the screen using the coordinates of a Point object.
   * @param point The Point object representing the coordinates of the point.
   * @param r The red component of the color (optional, default: 22).
   * @param g The green component of the color (optional, default: 14).
   * @param b The blue component of the color (optional, default: 237).
   */
  void drawPoint(int x, int y, int, int, int);

  /**
   * @brief Draws a line on the screen connecting two points.
   * @param line The Line object representing the line segment.
   * @param r The red component of the color (optional, default: 181).
   * @param g The green component of the color (optional, default: 14).
   * @param b The blue component of the color (optional, default: 237).
   */
  void drawLine(Line line, int, int, int);

  /**
   * @brief Draws a polygon on the screen.
   * @param polygon The Polygon object representing the polygon.
   * @param r The red component of the color (optional, default: 0).
   * @param g The green component of the color (optional, default: 40).
   * @param b The blue component of the color (optional, default: 200).
   */
  void drawPolygon(Polygon polygon, int, int, int, bool);

  ~Renderer() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
  }
};

int Renderer::normalizeX(int x) {
  float maxX = SCREEN_WIDTH / 2.3;
  scale = min(scale, abs((float)maxX / x));
  
  return SCREEN_WIDTH / 2 + scale * x;
}

int Renderer::normalizeY(int y) {
  float maxY = SCREEN_HEIGHT / 2.3;
  scale = min(scale, abs((float)maxY / y));
  
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

  // mace the points thicker
  SDL_RenderDrawPoint(renderer, x, y);
  SDL_RenderDrawPoint(renderer, x-1, y);
  SDL_RenderDrawPoint(renderer, x+1, y);
  SDL_RenderDrawPoint(renderer, x, y-1);
  SDL_RenderDrawPoint(renderer, x, y+1);

  // draw an X
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

void Renderer::drawPolygon(Polygon polygon, int r = 0, int g = 40, int b = 200, bool drawLastLine = true) {
  SDL_SetRenderDrawColor(renderer, r, g, b, 255);

  int numPoints = polygon.getSize();
  SDL_Point* points = new SDL_Point[numPoints];
  for (int i = 0; i < numPoints; i++) {
    Point p = polygon.getPoint(i);
    points[i].x = normalizeX(p.getX());
    points[i].y = normalizeY(p.getY());
  }
  SDL_RenderDrawLines(renderer, points, numPoints);
  if (drawLastLine)
    SDL_RenderDrawLine(renderer, points[numPoints - 1].x, points[numPoints - 1].y, points[0].x, points[0].y);
  delete[] points;
}

#endif