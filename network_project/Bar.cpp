#include "Bar.h"
#include <math.h>
#include <iostream>

using namespace std;

Bar::Bar() {

	point_top_left.set_x((window_w / 2) - 50);
	point_top_left.set_y(window_h - 50);
	height = 10;
	width = 100;
	point_bottom_right.set_x(point_top_left.get_x() + width);
	point_bottom_right.set_y(point_top_left.get_y() + height);
	speed = 1;
}

Bar::~Bar() {

}

void Bar::Update(int rot_x) {

	int current_top_x = point_top_left.get_x();
	int current_bottom_x = point_bottom_right.get_x();

	if (rot_x > 0) {
		speed = abs(speed) + rot_x;
	}
	else if (rot_x < 0) {
		speed = abs(speed) * -1 + rot_x;
	}
	point_top_left.set_x(current_top_x + speed);
	point_bottom_right.set_x(current_bottom_x + speed);
	speed = 1;
}

void Bar::Ball_detection(Ball *ball) {

	//ballの状態
	int radius = ball->get_radius();
	int ball_current_x = ball->get_x();
	int ball_current_y = ball->get_y();

	//バーの状態
	int bar_current_x = Get_top_left_x();
	int bar_current_y = Get_top_left_y();


	//上
	if ((ball_current_x >= bar_current_x && ball_current_x <= point_bottom_right.get_x()) &&
		ball_current_y + radius > bar_current_y
		) 
	{
		cout << "up " << "bar x:" << bar_current_x << "y: " << bar_current_y << endl;
		cout << "ball x:" << ball_current_x << "y: " << ball_current_y << endl;
		ball->reverse_speed_y(-1*abs(ball->get_speed_y()));
	}//下
	else if ((ball_current_x >= bar_current_x && ball_current_x <= point_bottom_right.get_x()) &&
		ball_current_y - radius > point_bottom_right.get_y()
		)
	{
		cout << "down " << "bar x:" << bar_current_x << "y: " << bar_current_y << endl;
		cout << "ball x:" << ball_current_x << "y: " << ball_current_y << endl;
		ball->reverse_speed_y(-1*abs(ball->get_speed_y()));
	}//左
	else if ((ball_current_y >= bar_current_y && ball_current_y <= point_bottom_right.get_y()) &&

		ball_current_x + radius >= bar_current_x && ball_current_x + radius <= point_bottom_right.get_x()
		)
	{
		cout << "left " << "bar x:" << bar_current_x << "y: " << bar_current_y << endl;
		cout << "ball x:" << ball_current_x << "y: " << ball_current_y << endl;
		ball->reverse_speed_x(abs(ball->get_speed_x()));
		ball->reverse_speed_y(-1 * ball->get_speed_y());
	}//右
	else if ((ball_current_y >= bar_current_y && ball_current_y <= point_bottom_right.get_y()) &&
		ball_current_x - radius <= point_bottom_right.get_x() && ball_current_x - radius >= point_bottom_right.get_x()
		)
	{
		cout <<  "right " << "bar x:" << bar_current_x << "y: " << bar_current_y << endl;
		cout << "ball x:" << ball_current_x << "y: " << ball_current_y << endl;
		ball->reverse_speed_x(abs(ball->get_speed_x()));
		ball->reverse_speed_y(-1*ball->get_speed_y());
	}

}


