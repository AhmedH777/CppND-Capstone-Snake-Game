#include "snake.h"
#include <cmath>
#include <iostream>
#include <vector>

void Snake::Update() {
  SDL_Point prev_cell{
      static_cast<int>(head_x),
      static_cast<int>(
          head_y)};  // We first capture the head's cell before updating.
  UpdateHead();
  SDL_Point current_cell{
      static_cast<int>(head_x),
      static_cast<int>(head_y)};  // Capture the head's cell after updating.

  // Update all of the body vector items if the snake head has moved to a new
  // cell.
  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
    UpdateBody(current_cell, prev_cell);
  }
}

void Snake::UpdateHead() {
  //std::cout<<"NExt DIr : "<<(int)direction<<std::endl;
  switch (direction) {
    case Direction::kUp:
      head_y -= speed;
      break;

    case Direction::kDown:
      head_y += speed;
      break;

    case Direction::kLeft:
      head_x -= speed;
      break;

    case Direction::kRight:
      head_x += speed;
      break;
  }

  // Wrap the Snake around to the beginning if going off of the screen.
  head_x = fmod(head_x + grid_width, grid_width);
  head_y = fmod(head_y + grid_height, grid_height);
}

void Snake::UpdateBody(SDL_Point &current_head_cell, SDL_Point &prev_head_cell) {
  // Add previous head location to vector
  body.push_back(prev_head_cell);

  if (!growing) {
    // Remove the tail from the vector.
    body.erase(body.begin());
  } else {
    growing = false;
    size++;
  }

  // Check if the snake has died.
  for (auto const &item : body) {
    if (current_head_cell.x == item.x && current_head_cell.y == item.y) {
      alive = false;
    }
  }
}

void Snake::GrowBody() { growing = true; }

// Inefficient method to check if cell is occupied by snake.
bool Snake::SnakeCell(int x, int y) {
  if (x == static_cast<int>(head_x) && y == static_cast<int>(head_y)) {
    return true;
  }
  for (auto const &item : body) {
    if (x == item.x && y == item.y) {
      return true;
    }
  }
  return false;
}

/* ############################## Snake AI ############################################*/

SnakeAI::SnakeAI(int grid_width, int grid_height) : Snake(grid_width, grid_height)
{
	this->toogle = false;
}

SnakeAI::~SnakeAI()
{

}

void SnakeAI::UpdateDirection(SDL_Point &foodPos)
{
	Point food  {(float)foodPos.x, (float)foodPos.y};
	Point headUp   {head_x        ,head_y - speed};
	Point headDown {head_x        ,head_y + speed};
	Point headRight{head_x + speed,head_y};
	Point headLeft {head_x - speed,head_y};

	std::vector<Point> Directions {std::move(headUp),std::move(headDown),std::move(headLeft),std::move(headRight)};

	float nearestDist = 99999;
	//std::cout<<"##############"<<std::endl;

	for (int i = 0; i < Directions.size();i++)
	{

		Point dir = Directions[i];
		bool  death = false;

		dir.x = fmod(dir.x + grid_width, grid_width);
		dir.y = fmod(dir.y + grid_height, grid_height);

		float deltaX   = (dir.x - food.x);
		float deltaY   = (dir.y - food.y);

		float distance = (deltaX * deltaX) + (deltaY * deltaY);


		for (auto const &item : body)
		{
			if ((int)dir.x == item.x && (int)dir.y == item.y)
			{
				death = true;
			}
		}



		//std::cout<<"AI distance Goal: "<<distance<<"  Dir ("<<dir.x<<","<<dir.y<<") "<<"Food ("<<food.x<<","<<food.y<<") Death : "<<death<<std::endl;

		if( ( distance < nearestDist ) &&
			(death == false) &&
			(this->toogle == false))
		{
		  nearestDist = distance;
		  this->direction = (Snake::Direction)i;
		}

		if (dirHist.size() == 4u)
		{
			if( ( dirHist[0] == dirHist[2] ) &&
				( dirHist[1] == dirHist[3] ))
			{
				this->toogle = true;
				dirHist.clear();
			}
		}
		else
		{
			this->toogle = false;
			dirHist.push_back(i);
		}

		/*
		for (h :dirHist)
		{
			std::cout<<"Dir Hist "<<h<<std::endl;
		}
		*/
	}
	//std::cout<<"Direction is "<<(int)this->direction<<" with Dist  = "<<nearestDist<<" toogle is "<<this->toogle<<std::endl;
	//std::cout<<"##############"<<std::endl;


}

void SnakeAI::UpdateAI(SDL_Point &foodPos)
{
	  SDL_Point prev_cell{
	      static_cast<int>(head_x),
	      static_cast<int>(
	          head_y)};  // We first capture the head's cell before updating.
	  UpdateDirection(foodPos);
	  UpdateHead();
	  SDL_Point current_cell{
	      static_cast<int>(head_x),
	      static_cast<int>(head_y)};  // Capture the head's cell after updating.

	  // Update all of the body vector items if the snake head has moved to a new
	  // cell.
	  if (current_cell.x != prev_cell.x || current_cell.y != prev_cell.y) {
	    UpdateBody(current_cell, prev_cell);
	  }
}
