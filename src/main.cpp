#include <iostream>
#include "controller.h"
#include "game.h"
#include "renderer.h"

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "####################################"<<std::endl;

  if(game.GetScoreSnake() > game.GetScoreSnakeAI() )
  {
	  std::cout<<"############ Human Wins ############"<<std::endl;
  }
  else
  {
	  std::cout<<"############## AI Wins #############"<<std::endl;
  }

  std::cout << "####################################"<<std::endl;
  std::cout << "Human Score"<<std::endl;
  std::cout << "###########"<<std::endl;
  std::cout << "Score: " << game.GetScoreSnake() << "\n";
  std::cout << "Size: " << game.GetSizeSnake() << "\n";
  std::cout << "####################"<<std::endl;
  std::cout << "AI Score"<<std::endl;
  std::cout << "########"<<std::endl;
  std::cout << "Score: " << game.GetScoreSnakeAI() << "\n";
  std::cout << "Size: " << game.GetSizeSnakeAI() << "\n";
  std::cout << "####################################"<<std::endl;

  return 0;
}
