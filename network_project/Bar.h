#pragma once
#include "Point.h"
#include "Ball.h"

extern int window_w;
extern int window_h;

class Bar
{
private:
	Point point_top_left;
	Point point_bottom_right;
	int width;
	int height;
	char speed;
public:
	Bar();
	~Bar();
	void Ball_detection(Ball *ball);
	inline int Get_top_left_x() { return point_top_left.get_x(); };
	inline int Get_top_left_y() { return point_top_left.get_y(); };
	inline int Get_bot_right_x() { return point_bottom_right.get_x(); };
	inline int Get_bot_right_y() { return point_bottom_right.get_y(); };
	inline int Get_height() { return height; };
	inline int Get_width() { return width; };
	void Update(int rot_x);

};