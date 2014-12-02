#include "Car.h"
#define _USE_MATH_DEFINES // for C++
#include <cmath>

/*
Constructor & Destructor
*/
Car::Car(float _x, float _y, float a, float s) : x(_x), y(_y), angle(a), speed(s)
{

}

/*
Getter & Setter
*/
float Car::getX()
{
	return x;
}

float Car::getSpeed()
{
	return speed;
}

float Car::getY()
{
	return y;
}

float Car::getAngle()
{
	return angle;
}

/*
Others
*/

void Car::move()
{
	x += cos(angle * M_PI / 180) * speed;
	y += sin(angle * M_PI / 180) * speed;
}

void Car::turnLeft()
{
	angle -= 2.f;
}

void Car::turnRight()
{
	angle += 2.f;
}

void Car::speedUp()
{
	if (speed <= 5.f)
		speed += 0.05f;
}

void Car::speedDown()
{
	if (speed >= 0)
		speed -= 0.05;
}

