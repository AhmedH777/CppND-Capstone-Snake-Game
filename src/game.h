#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"
#include "food.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,std::size_t target_frame_duration);
  int GetScoreSnake() const;
  int GetSizeSnake() const;
  int GetScoreSnakeAI() const;
  int GetSizeSnakeAI() const;
  Snake getSnake() const;

 private:
  Snake snake;
  SnakeAI snakeAI;
  Food foodObj;
/*
  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;
*/
  int score{0};
  int scoreAI{0};

  //void PlaceFood();
  void Update();
};

#endif
