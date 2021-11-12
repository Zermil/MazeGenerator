#include "Window.h"
#include <iostream>

Window::Window(const std::string& title, int width, int height) 
  : _title(title), _width(width), _height(height)
{
  _open = init();
}

Window::~Window()
{
  SDL_DestroyWindow(_window);
  SDL_DestroyRenderer(_renderer);

  SDL_Quit();
}

bool Window::init()
{
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
    std::cerr << "SDL -- Failed to initialize SDL\n";
    return false;
  }

  _window = SDL_CreateWindow(
    _title.c_str(),
    SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED,
    _width,
    _height,
    0
  );

  if (_window == nullptr) {
    std::cerr << "SDL -- Failed to initialize Window\n";
    return false;
  }

  _renderer = SDL_CreateRenderer(
    _window,
    -1,
    SDL_RENDERER_ACCELERATED
  );

  if (_renderer == nullptr) {
    std::cerr << "SDL -- Failed to initialize Renderer\n";
    return false;
  }

  return true;
}

void Window::getEvents()
{
  SDL_Event event;

  if (SDL_WaitEvent(&event)) {

    switch (event.type) {
    case SDL_QUIT:
      _open = false;
      break;
    }

  }
}

void Window::render() const
{
  SDL_RenderPresent(_renderer);

  SDL_SetRenderDrawColor(_renderer, 14, 14, 16, 255);
  SDL_RenderClear(_renderer);
}
