#include <iostream>
#include "food.h"

Food::Food(int grid_width,int grid_height)
		: _engine(_dev()),
		  _random_w(0, static_cast<int>(grid_width - 1)),
		  _random_h(0, static_cast<int>(grid_height - 1))
{
	_foodType = foodType::None;
	_food.x   = 0;
	_food.y   = 0;

	std::cout << "CREATING instance of Food at " << this << std::endl;
}

Food::~Food() // 1 : destructor
{
	std::cout << "DELETING instance of Food at " << this << std::endl;
}

Food::Food(const Food &source) // 2 : copy constructor
{
	_foodType = source._foodType;
	_food     = source._food;
	_engine   = source._engine;
	_random_w = source._random_w;
	_random_h = source._random_h;


	std::cout << "COPYING content of instance " << &source << " to instance " << this << std::endl;
}

Food &Food::operator=(const Food &source) // 3 : copy assignment operator
{
	std::cout << "ASSIGNING content of instance " << &source << " to instance " << this << std::endl;
	if (this == &source)
		return *this;
	_foodType = source._foodType;
	_food     = source._food;
	_engine   = source._engine;
	_random_w = source._random_w;
	_random_h = source._random_h;


	return *this;
}

Food::Food(Food &&source) // 4 : move constructor
{
	std::cout << "MOVING (c’tor) instance " << &source << " to instance " << this << std::endl;

	_foodType = source._foodType;
	_food     = source._food;
	_engine   = source._engine;
	_random_w = source._random_w;
	_random_h = source._random_h;

	source._foodType = foodType::None;
	source._food.x   = 0;
	source._food.y   = 0;
}

Food &Food::operator=(Food &&source) // 5 : move assignment operator
{
	std::cout << "MOVING (assign) instance " << &source << " to instance " << this << std::endl;
	if (this == &source)
		return *this;

	_foodType = source._foodType;
	_food     = source._food;
	_engine   = source._engine;
	_random_w = source._random_w;
	_random_h = source._random_h;

	source._foodType = foodType::None;
	source._food.x   = 0;
	source._food.y   = 0;
	return *this;
}

void Food::placeFood(Snake &snake)
{
	int x, y;

	// Get Random Food Type
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist((int)Normal, (int)MegaBooster);
    _foodType = (foodType)dist(gen);

    //std::cout<<"Food Type : "<<_foodType<<std::endl;

	// Get Radom Food Pos
	while (true)
	{
		x = _random_w(_engine);
		y = _random_h(_engine);
		// Check that the location is not occupied by a snake item before placing
		// food.
		//std::cout<<"Food PosX = "<<x<<" PosY = "<<y<<std::endl;

		if (!snake.SnakeCell(x, y))
		{
			_food.x = x;
			_food.y = y;

		  return;
		}
	}
}

SDL_Point Food::getFoodPos()
{
	return _food;
}

Food::foodType Food::getFoodTyp()
{
	return _foodType;
}
