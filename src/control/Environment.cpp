#include "Environment.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

Environment::Environment()
  : sdl(SDL_INIT_VIDEO),
    ttf(),
    font("resource/Cantarell-Regular.otf", 28) {
  window = SDL_CreateWindow("Chopter",
                            SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                            640, 480,
                            SDL_WINDOW_SHOWN);
  surface = SDL_GetWindowSurface(window);
}

Environment::~Environment() {
  if (window) {
    SDL_DestroyWindow(window);
  }
}
