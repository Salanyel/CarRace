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
	Car();
	Car(float _x, float _y, float angle, float speed);

	int getSpeedMin();

	float getX();
	float getY();
	float getAngle();
	void setAngle(float a);
	float getSpeed();
	void setSpeed(float s);
	void setSpeedValue(float s);
	void setSpeedMax(float s);
	void setLap(float l);
	float getLap();
	void setPosition(int _x, int _y);
	void initTheCar(float sV, float sM);

	void move(sf::Image& raceMask);
	bool calculateMaskCollision(sf::Image& raceMask);
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
	float m_speedValue;
	float m_speedMax;
	float m_speedMin;

	float m_nextX;
	float m_nextY;
	bool m_nextLap;
	int m_currentLap;	
	
	const float m_carRadius = 17;
	const float m_limit = 1;	
};

#endif // CAR_H