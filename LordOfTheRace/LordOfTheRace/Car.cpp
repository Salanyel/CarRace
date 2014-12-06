#include "Car.h"
#define _USE_MATH_DEFINES // for C++
#include <cmath>

/*
Constructor & Destructor
*/

Car::Car(float _x, float _y, float a, float s) : x(_x), y(_y), angle(a), speed(s)
{
	m_coefficient = 1;
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
	x += cos(angle * M_PI / 180) * m_coefficient * speed;
	y += sin(angle * M_PI / 180) * m_coefficient * speed;
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
	if (speed <= m_speedMax )
		speed += m_speedValue;
}

void Car::speedDown()
{
	if (speed >= m_speedMin)
		speed -= m_speedValue;
}

void Car::coefficientDown()
{
	m_coefficient -= m_speedValue;
}