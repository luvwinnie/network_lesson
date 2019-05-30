#pragma once
#include "Point.h"

extern int window_w;
extern int window_h;
extern int game_flag;

class Ball 
{
private:
	Point point;
	int radius;
	char speed_x;
	char speed_y;
	int game_end_flag;
public:
	Ball();
	~Ball();
	inline int get_radius() { return radius; };
	inline Point get_point() { return point; };
	inline int get_game_end_flag() { return game_end_flag;};
	inline int get_x() { return point.get_x(); };
	inline int get_y() { return point.get_y(); };
	inline char get_speed_x() { return speed_x; };
	inline char get_speed_y() { return speed_y; };
	inline void reverse_speed_x(char new_speed_x) { speed_x = new_speed_x; };
	inline void reverse_speed_y(char new_speed_y) { speed_y = new_speed_y; };
	void Update();
	void wall_collision_detect();
};

