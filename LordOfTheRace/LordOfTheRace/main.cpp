#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Car.h"

using namespace std;
using namespace sf;

const int WINDOW_HEIGHT = 800;
const int WINDOW_WIDTH = 600;
const String WINDOW_NAME = "Lord of the race";
const int FRAME_LIMIT = 32;

int main()
{
	RenderWindow app(VideoMode(WINDOW_HEIGHT, WINDOW_WIDTH, 32), WINDOW_NAME);
	app.setFramerateLimit(FRAME_LIMIT);

	Texture raceTexture, raceMaskTexture, carImage;
	Sprite raceSprite, raceMaskSprite, carSprite;

	if (!raceTexture.loadFromFile("./Assets/Img/race01.png"))
	{
		cout << "Error during the loading of the race." << endl;
		return EXIT_FAILURE;
	}//*/

	if (!carImage.loadFromFile("./Assets/Img/car.png"))
	{
		cout << "Error during the loading of the car." << endl;
		return EXIT_FAILURE;
	}

	if (!raceMaskTexture.loadFromFile("./Assets/Img/mask_race01.png"))
	{
		cout << "Error during the loading of the race mask." << endl;
		return EXIT_FAILURE;
	}

	raceSprite.setTexture(raceTexture);
	raceMaskSprite.setTexture(raceMaskTexture);
	carSprite.setTexture(carImage);	

	carSprite.setOrigin(20, 34);
	carSprite.setScale(0.5, 0.5);

	Car car(790, 1215, 0, 0);

	Vector2f center(car.getX(), car.getY());
	Vector2f halfSize(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4);
	View view(center, halfSize);
	app.setView(view);

	while (app.isOpen())
	{
		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed)
				app.close();

			if (event.type == Event::KeyPressed)
				if (event.key.code == Keyboard::Escape)
					app.close();
		}

		/*
		Manage of the keyboard input
		*/

		if (Keyboard::isKeyPressed(Keyboard::Left))
		{
			car.turnLeft();
			carSprite.setRotation(car.getAngle());
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			car.turnRight();
			carSprite.setRotation(car.getAngle());
		}

		if (Keyboard::isKeyPressed(Keyboard::Up))
		{
			car.speedUp();
		}

		if (Keyboard::isKeyPressed(Keyboard::Down))
		{
			car.speedDown();
		}

		/*
		Display
		*/
		app.clear();
		car.move();		
		cout << "Car : " << car.getSpeed() <<  endl;
		view.setCenter(car.getX(), car.getY());
		app.draw(raceSprite);
		app.setView(view);

		carSprite.setPosition(car.getX(), car.getY());		

		app.draw(carSprite);

		app.display();
	}

	return EXIT_SUCCESS;

}

