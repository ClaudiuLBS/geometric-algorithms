#include <iostream>
#include "renderer.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 800;

int main(int argc, char* argv[]) {
  Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT, "nigger");
  Line line(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

  bool running = true;
  while (running) {
    if (renderer.shouldQuit())
      running = false;
    
    renderer.clear();
    renderer.drawAxis();
    // renderer.drawLine(line);
    renderer.drawPoint(-10, -10);
    renderer.drawPoint(10, -10);
    renderer.drawPoint(10, 10);
    renderer.drawPoint(-10, 10);
    renderer.update();
  }
  return 0;
}
