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

protected:
private:
	float x, y;
	float angle;
	float speed;
};

#endif // CAR_H
