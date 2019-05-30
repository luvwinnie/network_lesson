#pragma once
//#include "Bar.h";
//#include "Ball.h";

extern int window_w;
extern int window_h;

class Point
{
private:
	int x;
	int y;
public:
	Point();
	~Point();
	int get_y() { return y; };
	int get_x() { return x; };
	inline void set_x(int x_new) { x = x_new; };
	inline void set_y(int y_new) { y = y_new; };

};

