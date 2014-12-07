#include "GraphicEngine.h"

using namespace sf;
using namespace std;

GraphicEngine::GraphicEngine(RenderWindow& w) : window(w)
{	
}

GraphicEngine::~GraphicEngine()
{
}

string GraphicEngine::initGraphicEngine()
{
	string ctrlGraphicEngine = "";
	
	ctrlGraphicEngine = loadTexture();

	if (ctrlGraphicEngine != "")
		return ctrlGraphicEngine;
	
	ctrlGraphicEngine = initText();

	if (ctrlGraphicEngine != "")
		return ctrlGraphicEngine;

	loadSprite();
	initView();
	initVar();		

	//Init the View	
	Vector2f size(VIEW_SIZE_X, VIEW_SIZE_Y);
	View view;

	return ctrlGraphicEngine;
}

string GraphicEngine::loadTexture()
{

	string ctrlInitGraphicEngine;

	if (!m_T_speedMeter.loadFromFile("./Assets/Img/speedMeter02.png"))
	{
		ctrlInitGraphicEngine = "Error during the loading of the speedMeter.";
		cerr << ctrlInitGraphicEngine << endl;
		return ctrlInitGraphicEngine;
	}
	else
		cout << "Speed meter loaded." << endl;

	if (!m_T_hand.loadFromFile("./Assets/Img/hand.png"))
	{
		ctrlInitGraphicEngine = "Error during the loading of the speedMeter hand.";
		cerr << ctrlInitGraphicEngine << endl;
		return ctrlInitGraphicEngine;
	}
	else
		cout << "hand loaded." << endl;

	return "";	
}

string GraphicEngine::initText()
{
	string ctrlInitFont;

	if (!m_font.loadFromFile("./Assets/Font/SF Sports Night.ttf"))
	{
		ctrlInitFont = "Error during the loading of the speedMeter.";
		cerr << ctrlInitFont << endl;
		return ctrlInitFont;
	}
	else
		cout << "Font \"SF Sports Night\" loaded." << endl;

	return "";

	m_speedText.setFont(m_font);
	m_speedText.setString("THIS IS SPARTA !");
	m_speedText.setCharacterSize(24);
	m_speedText.setColor(Color::Blue);	
	m_speedText.setStyle(sf::Text::Bold);
	m_speedText.setPosition(50, 50);
	//m_speedText.setPosition(SPEED_METER_X + 150, SPEED_METER_Y + 150);

}

void GraphicEngine::loadSprite()
{
	m_S_speedMeter.setTexture(m_T_speedMeter);
	m_S_speedMeter.setScale(m_speedMeterScale, m_speedMeterScale);
	m_S_speedMeter.setPosition(SPEED_METER_X, SPEED_METER_Y);

	m_S_hand.setTexture(m_T_hand);
	m_S_hand.setScale(m_handScale, m_handScale);
	m_S_hand.setPosition(SPEED_METER_X + 150, SPEED_METER_Y + 150);
	m_S_hand.setOrigin(57, 716);
	m_S_hand.setRotation(HAND_BEGIN_POSITION);
}

void GraphicEngine::initView()
{
}

void GraphicEngine::initVar()
{
}

void GraphicEngine::draw(float speed)
{
	string speedValue;
	ostringstream ss;

	m_S_hand.setRotation(speed * SPEED_ADAPTOR + HAND_BEGIN_POSITION);
	m_speedText.setString(ss.str());
	speedValue = speed*SPEED_ADAPTOR;
	ss << speedValue;

	// TODO : faire apparaître le text
	window.setView(viewMeter);		
	window.draw(m_S_speedMeter);			
	window.draw(m_S_hand);
	window.draw(m_speedText);
}