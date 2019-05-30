#include "Ball.h"
#include <iostream>

using namespace std;

Ball::Ball()
{
	game_end_flag = 0;
	radius = 10;
	speed_x = 7;
	speed_y = 4;
	point.set_x( window_w / 2);
	point.set_y( window_h / 2);
}


Ball::~Ball()
{
}


void Ball::Update() {
	int current_x = point.get_x();
	int current_y = point.get_y();
	point.set_x(current_x + speed_x);
	point.set_y(current_y + speed_y);
	return;
}

void Ball::wall_collision_detect() {

	int current_x = point.get_x();
	int current_y = point.get_y();
	
	//
	if (current_x - radius <= 0 ) {
		cout << "x:"  << current_x << endl;
		speed_x *= -1;
	}
	else if (current_x + radius >= 640)
	{
		cout << "x:" << current_x << endl;
		speed_x *= -1;
	}
	else if (current_y - radius <= 0) {
		cout << "y:" << current_y << endl;
		speed_y *= -1;
	}
	else if (current_y + radius >= 480) {
		/*cout << "y:" << current_y << endl;
		speed_y *= -1;*/
		game_end_flag = 1;
	}
	
	
}