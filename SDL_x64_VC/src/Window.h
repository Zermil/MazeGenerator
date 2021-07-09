#ifndef WINDOW_H
#define WINDOW_H

#include <string>
#include <SDL.h>

class Window {
public:
  Window(const std::string& title, int width, int height);
  ~Window();

  void getEvents();
  void render() const;
  inline bool isOpen() const { return _open; }

private:
  bool init();

private:
  std::string _title;
  int _width;
  int _height;

  bool _open = false;

  SDL_Window* _window = nullptr;

protected:
  SDL_Renderer* _renderer = nullptr;
};

#endif // WINDOW_H