#include "Car.h"

/*
Constructor & Destructor
*/

Car::Car()
{
	m_currentLap = 1;
	m_nextLap = false;
	m_speedMin = 0;
}

Car::Car(float _x, float _y, float a, float s) : x(_x), y(_y), angle(a), speed(s)
{
	m_currentLap = 1;
	m_nextLap = false;
	m_speedMin = 0;
	m_speedValue = 0.1f;
	m_speedMax = 6;
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

void Car::setSpeed(float s)
{
	speed = s;
}

void Car::setSpeedValue(float s)
{
	m_speedValue = s;
}

int Car::getSpeedMin()
{
	return m_speedMin;
}

void Car::setSpeedMax(float s)
{
	m_speedMax = s;
}

float Car::getY()
{
	return y;
}

float Car::getAngle()
{
	return angle;
}

void Car::setAngle(float a)
{
	angle = a;
}

float Car::getLap()
{
	return m_currentLap;
}

void Car::setPosition(int _x, int _y)
{
	x = _x;
	y = _y;
}

void Car::initTheCar(float sV, float sM)
{
	m_speedValue = sV;
	m_speedMax = sM;
}

/*
Others
*/

void Car::move(sf::Image& maskRace)
{
	
	m_nextX = x + cos(angle * M_PI / 180) *  speed;
	m_nextY = y + sin(angle * M_PI / 180) * speed;

	if (calculateMaskCollision(maskRace))
	{
		x += cos(angle * M_PI / 180) * speed;
		y += sin(angle * M_PI / 180) * speed;
	}		
}

bool Car::calculateMaskCollision(sf::Image& raceMask)
{
	sf::Color nextPos = raceMask.getPixel(m_nextX, m_nextY);

	if (nextPos == sf::Color::Black)
	{
		speedDownFast();
		return false;
	}

	if (nextPos == sf::Color(255, 255, 0))
	{
		m_nextLap = true;
	}

	if (nextPos == sf::Color(0, 0, 128))
	{
		if (m_nextLap)
		{
			m_currentLap++;
			m_nextLap = false;
		}
	}

	if (nextPos == sf::Color::White)
		speedDownFast();

	return true;
}

void Car::turnLeft()
{
	float turn = 4.f;
	float coef = 1 - (speed / m_speedMax);

	if (coef < 0.5)
		coef = 0.5;
	
	angle -= (coef * turn);
} 

void Car::turnRight()
{
	float turn = 4.f;
	float coef = 1 - (speed / m_speedMax);

	if (coef < 0.5)
		coef = 0.5;

	angle += (coef * turn);
}

void Car::speedUp()
{
	if (speed <= m_speedMax)
		speed += m_speedValue;
	else
		speed = m_speedMax + m_speedValue;
}

void Car::speedDown()
{
	if (speed >= m_speedMin)
		speed -= m_speedValue;

	if (speed < 0)
		speed = 0;

}

void Car::speedDownFast()
{
	if (speed - (m_speedValue + 0.05) >= m_limit)
		speed -= (m_speedValue + 0.05) ;
	else
		speed = m_limit;
}