#include "game.h"
#include <iostream>
#include "SDL.h"
#include <thread>


Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
	  snakeAI(grid_width, grid_height),
	  foodObj(grid_width,grid_height)
{
  foodObj.placeFood(snake);
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, snakeAI, foodObj);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}
/*
void Game::PlaceFood() {
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    SDL_Point food = foodObj.getFoodPos();

    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      return;
    }
  }
}
*/
void Game::Update() {
  if (!snake.alive || !snakeAI.alive) return;

  SDL_Point food = foodObj.getFoodPos();

  snake.Update();
  snakeAI.UpdateAI(food);

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    score += (int)foodObj.getFoodTyp();

    foodObj.placeFood(snake);
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }

  // ############ Update SnakeAI ################
  new_x = static_cast<int>(snakeAI.head_x);
  new_y = static_cast<int>(snakeAI.head_y);

  food = foodObj.getFoodPos();
  // Check if there's food over here
  if (food.x == new_x && food.y == new_y)
  {
    scoreAI += (int)foodObj.getFoodTyp();

    foodObj.placeFood(snakeAI);
    // Grow snake and increase speed.
    snakeAI.GrowBody();
    snakeAI.speed += 0.001;
  }
}

int Game::GetScoreSnake() const { return score; }
int Game::GetSizeSnake() const { return snake.size; }
int Game::GetScoreSnakeAI() const { return scoreAI; }
int Game::GetSizeSnakeAI() const { return snakeAI.size; }
