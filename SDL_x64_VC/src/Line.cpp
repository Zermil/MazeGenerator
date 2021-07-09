#include "Line.h"

Line::Line(const Window& window, int x1, int y1, int x2, int y2)
  : Window(window), _x1(x1), _y1(y1), _x2(x2), _y2(y2)
{}

void Line::draw() const
{
  SDL_SetRenderDrawColor(_renderer, 255, 255, 255, 255);
  SDL_RenderDrawLine(_renderer, _x1, _y1, _x2, _y2);
}