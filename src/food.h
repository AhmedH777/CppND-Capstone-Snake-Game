#ifndef FOOD_H
#define FOOD_H

#include <random>
#include "SDL.h"
#include "snake.h"

class Food
{
 public:
	enum foodType { None, Normal, Booster, MegaBooster };

	// Implement Rule of Five
	Food(int grid_width,int grid_height);
	~Food();
	Food(const Food &source); 			// 2 : copy constructor
	Food &operator=(const Food &source);  // 3 : copy assignment operator
	Food(Food &&source); 					// 4 : move constructor
	Food &operator=(Food &&source); 		// 5 : move assignment operator

	void placeFood(Snake &snake);
	SDL_Point getFoodPos();
	foodType  getFoodTyp();


 private:

	SDL_Point _food;
	foodType _foodType;

	std::random_device _dev;
	std::mt19937 _engine;
	std::uniform_int_distribution<int> _random_w;
	std::uniform_int_distribution<int> _random_h;



};

#endif
