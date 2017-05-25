#include <SDL2/SDL_events.h>
#include <SDL2/SDL_timer.h>
#include "Event.hpp"

Event::Event() {
  quit = false;
  timeout = 1000/30;
  resetTime();
}

bool Event::waitForStepTime() {
  hasPressedKey = false;
  while(checkEvents()) {
    if (isTime()) {
      resetTime();
      break;
    }
  }
  return !quit;
}

bool Event::checkForButtonDown() const {
  const Uint8* currentKeyStates = SDL_GetKeyboardState(NULL);
  return currentKeyStates[SDL_SCANCODE_UP] || hasPressedKey;
}

bool Event::checkEvents() {
  SDL_Event event;
  while (!quit && SDL_PollEvent(&event) != 0) {
    if (!processEvent(event)) {
      break;
    }
  }
  return !quit;
}

bool Event::processEvent(const SDL_Event & event) {
  switch (event.type) {
  case SDL_QUIT:
    quit = true;
    return false;
  case SDL_KEYDOWN:
    if (event.key.keysym.sym == SDLK_UP) {
      hasPressedKey = true;
    }
    break;
  }
  return true;
}

bool Event::isTime() {
  return prevTime + timeout <= SDL_GetTicks();
}

void Event::resetTime() {
  prevTime = SDL_GetTicks();
}
