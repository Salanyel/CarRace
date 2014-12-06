#ifndef CAR_H
#define CAR_H

class Car
{

public:
	Car(float _x, float _y, float angle, float speed);

	float getX();
	float getY();
	float getAngle();
	float getSpeed();

	void move();
	void turnLeft();
	void turnRight();
	void speedUp();
	void speedDown();
	void coefficientDown();

protected:
private:
	float x, y;
	float angle;
	float speed;
	float m_coefficient;	

	const float m_speedValue = 0.1;
	const float m_speedMax = 6;
	const float m_speedMin = 0;
	const float m_carRadius = 35;
	
};

#endif // CAR_H
