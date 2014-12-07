#ifndef GRAPHIC_ENGINE
#define GRAPHIC_ENGINE

#include <SFML\Graphics.hpp>
#include "SpeedMeter.h"
#include <string>
#include <iostream>
#include <sstream>

class GraphicEngine
{
public:
	GraphicEngine(sf::RenderWindow& w);
	~GraphicEngine();

	std::string initGraphicEngine();
	std::string loadTexture();
	std::string initText();
	void loadSprite();
	void initView();
	void initVar();
	void draw(float speed);	

private:

	sf::RenderWindow& window;
	sf::View viewMeter;

	//Speed meter
	SpeedMeter m_speledMeter;
	sf::Texture m_T_speedMeter;
	sf::Sprite m_S_speedMeter;	
	
	//Hand
	sf::Texture m_T_hand;
	sf::Sprite m_S_hand;
	
	//Text
	sf::Text m_speedText;	
	sf::Font m_font;

	const double m_speedMeterScale = 0.1;
	const double m_handScale = 0.15;
	const double SPEED_METER_X = 0;
	const double SPEED_METER_Y = 800;	
	const double HAND_BEGIN_POSITION = -110;
	const double SPEED_ADAPTOR = 20.98;
	//Min : -110 // Max : 18

	const int VIEW_SIZE_X = 200;
	const int VIEW_SIZE_Y = 200;
	
};

#endif