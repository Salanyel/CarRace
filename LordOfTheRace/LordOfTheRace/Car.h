#ifndef CAR_H
#define CAR_H

#include <SFML\Graphics\Image.hpp>
#include <SFML\Graphics\Color.hpp>
#include <iostream>

#ifndef M_PI
	#define M_PI 3.14159265358979323846
#endif

class Car
{

public:
	Car(float _x, float _y, float angle, float speed);

	float getX();
	float getY();
	float getAngle();
	float getSpeed();

	void move(sf::Image& raceMask);
	bool calculateNextMove(sf::Image& raceMask);
	void turnLeft();
	void turnRight();
	void speedUp();
	void speedDown();	
	void speedDownFast();
	void coefficientDown();
	void resetCoefficient();

protected:
private:
	float x, y;	
	float angle;
	float speed;
	
	float m_nextX;
	float m_nextY;

	const float m_speedValue = 0.1;
	const float m_speedMax = 6;
	const float m_speedMin = 0;
	const float m_carRadius = 17;
	const float m_limit = 1;	
};

#endif // CAR_H
