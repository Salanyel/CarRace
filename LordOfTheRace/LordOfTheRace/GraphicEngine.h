#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include <SFML\Graphics.hpp>
#include "SpeedMeter.h"
#include <string>
#include <iostream>
#include <sstream>
#include "Chronometer.h"

class GraphicEngine
{
public:
	GraphicEngine(sf::RenderWindow& w);
	~GraphicEngine();

	std::string initGraphicEngine();
	std::string loadTexture();
	std::string setMinimap(std::string id);
	std::string initText();
	sf::Text getText();
	void loadSprite();
	void initView();
	void initVar();
	void setStep(float h, float t);
	void newLap();
	void restartChronometer();
	void setCarOnMiniMap(int x, int y);
	void setTextForDraw(float speed, int lap, int maxLap);
	void draw(float speed, int lap, int maxLap);
	void drawFinalScreen();

private:

	sf::RenderWindow& window;
	sf::View viewMeter;

	//Minimap
	sf::Texture m_T_minimap;
	sf::Sprite m_minimap;
	sf::CircleShape m_player;

	//Speed meter
	sf::Texture m_T_speedMeter;
	sf::Sprite m_S_speedMeter;	
	
	//Hand
	sf::Texture m_T_hand;
	sf::Sprite m_S_hand;
	
	//Text
	sf::Text m_speedText;	
	sf::Text m_lap;
	sf::Text m_finalScreen;
	sf::Text m_currentTimer;
	sf::Text m_bestLapText;
	sf::Font m_font;	

	//Chronometer
	Chronometer m_chronometer;

	int m_bestLap = -1;
	double SPEED_ADAPTOR = 39.016;
	double SPEED_ADAPTATOR_TEXT = 32.787;

	const double m_speedMeterScale = 0.1;
	const double m_handScale = 0.15;
	const double SPEED_METER_X = 100;
	const double SPEED_METER_Y = 600;	
	const double HAND_BEGIN_POSITION = -123;	
	const int HAND_X = 220;
	const int HAND_Y = 725;	
	const int VIEW_SIZE_X = 800;
	const int VIEW_SIZE_Y = 600;
	const int MAP_X = 100;
	const int MAP_Y = 200;
	
};

#endif