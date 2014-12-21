#include <cstdlib>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Car.h"
#include "GraphicEngine.h"
#include "CXBOXController.h"
#include "XmlLoader.h"

using namespace std;
using namespace sf;

const int WINDOW_WIDTH = 800;//1200
const int WINDOW_HEIGHT = 600;//900
const String WINDOW_NAME = "Lord of the race";
const int FRAME_LIMIT = 32;
int LAP_MAX = 3;

int main()
{
	RenderWindow app(VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32), WINDOW_NAME);
	GraphicEngine * m_graphicEngine = new GraphicEngine(app);
	XmlLoader * m_xmlLoader = new XmlLoader();
	int currentLap;
	int previousLap = 1;
	string initValue = m_graphicEngine->initGraphicEngine();
	string initValue2 = m_xmlLoader->loadFile();
	int m_gamePadDirection = 0;
	int carModel = 3;
	int raceModel = 2;

	//TODO : XInput
	CXBOXController* Player1;
	CXBOXController* Player2;
	Player1 = new CXBOXController(1);
	Player2 = new CXBOXController(2);
	XINPUT_STATE m_state;

	if (initValue != "" || initValue2 != "")
	{
		cerr << initValue << endl;
		return EXIT_FAILURE;
	}
	else
		cout << endl << "####################" << endl << "Graphic engine initialized." << endl << "####################" << endl << endl;
	

	app.setFramerateLimit(FRAME_LIMIT);

	Texture raceTexture, carImage;
	Image raceMask;
	Sprite raceSprite, *carSprite;

	//Car car(790, 1215, 0, 0);
	Car car;

	initValue = m_xmlLoader->initGame(carModel, raceModel, car, m_graphicEngine, carImage, raceTexture, raceMask, LAP_MAX);

	if (initValue != "")
	{
		cout << initValue << endl;
		return EXIT_FAILURE;
	}	

	raceSprite.setTexture(raceTexture);
	carSprite = new Sprite();
	carSprite->setTexture(carImage);	

	m_xmlLoader->setOrigin(*carSprite);
	carSprite->setScale(0.5, 0.5);	

	Vector2f center(car.getX(), car.getY());
	Vector2f halfSize(WINDOW_WIDTH / 3.5, WINDOW_HEIGHT / 3.5);
	View view(center, halfSize);	

	while (app.isOpen())
	{
		m_state = Player1->GetState();
		XINPUT_STATE m_state2 = Player2->GetState();
		m_gamePadDirection = 0;

		float LX = m_state.Gamepad.sThumbLX;

		//determine how far the controller is pushed
		float magnitude = sqrt(LX*LX + LX*LX);

		//determine the direction the controller is pushed
		float normalizedLX = LX / magnitude;

		float normalizedMagnitude = 0;

		if (magnitude > XINPUT_GAMEPAD_LEFT_THUMB_DEADZONE)
		{
			if (normalizedLX < 0)
				m_gamePadDirection = -1;
			else
				m_gamePadDirection = 1;

		}
		else //if the controller is in the deadzone zero out the magnitude
		{
			magnitude = 0.0;
			normalizedMagnitude = 0.0;
		}

		Event event;
		while (app.pollEvent(event))
		{
			if (event.type == Event::Closed || (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_BACK))// || (m_state.Gamepad.wButtons & XINPUT_GAMEPAD_BACK))// || m_gamepad.isPressed()
				app.close();

			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
					app.close();
			}				

			if (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_START)
			{
				initValue = m_xmlLoader->initGame(carModel, raceModel, car, m_graphicEngine, carImage, raceTexture, raceMask, LAP_MAX);

				if (initValue != "")
				{
					cout << initValue << endl;
					return EXIT_FAILURE;
				}

				carSprite = new Sprite();
				carSprite->setTexture(carImage);

				m_xmlLoader->setOrigin(*carSprite);
				carSprite->setScale(0.5, 0.5);

				m_graphicEngine->restartChronometer();
			}
		}

		/*
		Manage of the keyboard input
		*/

		if (Keyboard::isKeyPressed(Keyboard::Left) || (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_LEFT) || m_gamePadDirection == -1)
		{
			if (car.getSpeed() > 0)
			{
				car.turnLeft();
				carSprite->setRotation(car.getAngle());
			}			
		}

		if (Keyboard::isKeyPressed(Keyboard::Right) || (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_DPAD_RIGHT) || m_gamePadDirection == 1)
		{
			if (car.getSpeed() > 0)
			{
				car.turnRight();
				carSprite->setRotation(car.getAngle());
			}
		}

		if (Keyboard::isKeyPressed(Keyboard::Up) || (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_A))
		{
			car.speedUp();
		} else {
			car.speedDown();
		}

		if (Keyboard::isKeyPressed(Keyboard::Down) || (Player1->GetState().Gamepad.wButtons & XINPUT_GAMEPAD_X))
		{
			car.speedDown();
		}

		/*
		Display
		*/
		currentLap = car.getLap();
		app.clear();

		if (previousLap != currentLap)
		{
			m_graphicEngine->newLap();
			previousLap = currentLap;
		}

		if (currentLap == LAP_MAX + 1)
		{
			m_graphicEngine->drawFinalScreen();
			
		} else { 
			car.move(raceMask);								

			app.draw(raceSprite);
	
			//This 3 lines are linked. Cause of the "View"
			m_graphicEngine->setCarOnMiniMap(car.getX(), car.getY());
			m_graphicEngine->draw(car.getSpeed(), currentLap, LAP_MAX);
			app.setView(view);
			view.setCenter(car.getX(), car.getY());

			carSprite->setPosition(car.getX(), car.getY());		
			app.draw(*carSprite);
		}
		app.display();
	}

	return EXIT_SUCCESS;

}