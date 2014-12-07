#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "GraphicEngine.h"

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;//1200
const int WINDOW_HEIGHT = 600;//900
const String WINDOW_NAME = "Lord of the race";
const int FRAME_LIMIT = 32;

int main()
{
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_NAME);
	GraphicEngine * m_graphicEngine = new GraphicEngine(app);

	string initValue = m_graphicEngine->initGraphicEngine();

	if (initValue != "")
	{
		cerr << initValue << endl;
		return EXIT_FAILURE;
	}
	else
		cout << endl << "####################" << endl << "Graphic engine initialized." << endl << "####################" << endl << endl;
	

	app.setFramerateLimit(FRAME_LIMIT);

	Texture raceTexture, carImage;
	Image raceMask;
	Sprite raceSprite, carSprite;

	if (!raceTexture.loadFromFile("./Assets/Img/race01.png"))
	{
		cerr << "Error during the loading of the race." << endl;
		return EXIT_FAILURE;
	}
	else
		cout << "race01 loaded." << endl;

	if (!carImage.loadFromFile("./Assets/Img/car.png"))
	{
		cerr << "Error during the loading of the car." << endl;
		return EXIT_FAILURE;
	}
	else
		cout << "car loaded." << endl;

	if (!raceMask.loadFromFile("./Assets/Img/mask_race01.png"))
	{
		cerr << "Error during the loading of the race mask." << endl;
		return EXIT_FAILURE;
	}
	else
		cout << "mask_race01 loaded." << endl;

	raceSprite.setTexture(raceTexture);
	carSprite.setTexture(carImage);	

	carSprite.setOrigin(34, 20);
	carSprite.setScale(0.5, 0.5);

	Car car(790, 1215, 0, 0);

	Vector2f center(car.getX(), car.getY());
	Vector2f halfSize(WINDOW_WIDTH / 4, WINDOW_HEIGHT / 4);
	View view(center, halfSize);	

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
			if (car.getSpeed() > 0)
			{
				car.turnLeft();
				carSprite.setRotation(car.getAngle());
			}			
		}

		if (Keyboard::isKeyPressed(Keyboard::Right))
		{
			if (car.getSpeed() > 0)
			{
				car.turnRight();
				carSprite.setRotation(car.getAngle());
			}
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
		car.move(raceMask);								

		app.draw(raceSprite);
	
		//This 3 lines are linked. Cause of the "View"
		m_graphicEngine->draw(car.getSpeed());
		app.setView(view);
		view.setCenter(car.getX(), car.getY());

		carSprite.setPosition(car.getX(), car.getY());		
		app.draw(carSprite);		

		app.display();
	}

	return EXIT_SUCCESS;

}