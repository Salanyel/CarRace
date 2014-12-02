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

	Texture backgroundImage, carImage;
	Sprite backgroundSprite, carSprite;

	if (!backgroundImage.loadFromFile("./Assets/Img/race.png"))
	{
		cout << "Error during the loading of the race." << endl;
		return EXIT_FAILURE;
	}//*/

	if (!carImage.loadFromFile("./Assets/Img/car.png"))
	{
		cout << "Error during the loading of the car." << endl;
		return EXIT_FAILURE;
	}

	backgroundSprite.setTexture(backgroundImage);
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
		view.setCenter(car.getX(), car.getY());
		app.draw(backgroundSprite);
		app.setView(view);

		carSprite.setPosition(car.getX(), car.getY());
		app.draw(carSprite);

		app.display();
	}

	return EXIT_SUCCESS;

}

