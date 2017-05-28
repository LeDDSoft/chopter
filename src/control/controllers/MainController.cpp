#include "../../core/Point.hpp"
#include "../Environment.hpp"
#include "../Logic.hpp"
#include "../color.hpp"
#include "MainController.hpp"
#include "../score.hpp"
#include <cstdlib>
#include <cstdio>
#include <SDL2pp/Rect.hh>
#include <SDL2pp/Point.hh>

extern Environment environment;

#define C_SCREEN C_BLACK

MainController::MainController(Logic * logic)
  : Controller(logic) {
  const int componentWidth = 128;
  const int componentHeight = 48;
  const SDL2pp::Point roomSize = environment.window.GetSize();
  const int centerX = (roomSize.x - componentWidth) / 2;
  btnPlay = SDL2pp::Rect(centerX, componentHeight,
                         componentWidth, componentHeight);
  btnPlay.setColor(C_BLUE);
  labelPlay.setText("Play");
  labelPlay.setRect(btnPlay);
  labelPlay.halign = Label::Center; labelPlay.valign = Label::Middle;
  btnQuit = SDL2pp::Rect(centerX, roomSize.y - 2 * componentHeight,
                         componentWidth, componentHeight);
  btnQuit.setColor(C_RED);
  labelQuit.setText("Quit");
  labelQuit.setRect(btnQuit);
  labelQuit.halign = Label::Center; labelQuit.valign = Label::Middle;
  int score = readScore();
  sprintf(highScoreText, "HighScore: %i", score);
  labelScore.setText(highScoreText);
  labelScore.setRect(SDL2pp::Rect(centerX, 0,
                                  componentWidth, componentHeight));
  labelScore.halign = Label::Center; labelScore.valign = Label::Top;
};

void MainController::loop() {
  draw();
  while(checkEvents()) {
    draw();
  }
}

static SDL_Rect rect;

void MainController::draw() {
  rect.x = 0; rect.y = 0;
  rect.w = 640; rect.h = 480;
  SDL_FillRect(environment.surface, &rect, C_SCREEN);
  btnPlay.draw();
  btnQuit.draw();
  labelPlay.draw();
  labelQuit.draw();
  labelScore.draw();
  environment.renderer.Present();
}

bool MainController::processEvent(const SDL_Event & event) {
  if (!Event::processEvent(event)) {
    logic->nextState(Logic::Quit);
    return false;
  }
  if (event.type == SDL_MOUSEMOTION) {
    Point<int> mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    if (btnPlay.checkClick(mouse)) {
      btnPlay.select();
    } else {
      btnPlay.unselect();
    }
    if (btnQuit.checkClick(mouse)) {
      btnQuit.select();
    } else {
      btnQuit.unselect();
    }
  } else if (event.type == SDL_MOUSEBUTTONDOWN) {
    Point<int> mouse;
    SDL_GetMouseState(&mouse.x, &mouse.y);
    if (btnPlay.checkClick(mouse)) {
      logic->nextState(Logic::PlayGame);
      quit = true;
      return false;
    }
    if (btnQuit.checkClick(mouse)) {
      logic->nextState(Logic::Quit);
      quit = true;
      return false;
    }
  }
  return true;
}
