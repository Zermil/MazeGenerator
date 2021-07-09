#ifndef LINE_H
#define LINE_H

#include "Window.h"

class Line : public Window {
public:
  Line(const Window& window, int x1, int y1, int x2, int y2);

  void draw() const;

private:
  int _x1, _y1;
  int _x2, _y2;
};

#endif // !LINE_H
