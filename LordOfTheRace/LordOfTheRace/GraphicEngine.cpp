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
	initView();
	window.setView(viewMeter);

	string ctrlGraphicEngine = "";
	
	ctrlGraphicEngine = loadTexture();

	if (ctrlGraphicEngine != "")
		return ctrlGraphicEngine;
	
	ctrlGraphicEngine = initText();

	if (ctrlGraphicEngine != "")
		return ctrlGraphicEngine;

	loadSprite();	
	initVar();			

	return ctrlGraphicEngine;
}

Text GraphicEngine::getText()
{
	return m_speedText;
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
		ctrlInitFont = "Error during the loading of the font.";
		cerr << ctrlInitFont << endl;
		return ctrlInitFont;
	}
	else
		cout << "Font \"SF Sports Night\" loaded." << endl;

	m_speedText.setFont(m_font);
	m_speedText.setString("0");
	m_speedText.setCharacterSize(24);
	m_speedText.setColor(Color(245, 198, 80));	
	m_speedText.setPosition(HAND_X - 20, HAND_Y + 10);

	m_lap.setFont(m_font);
	m_lap.setString("Lap : 1 / 3");
	m_lap.setCharacterSize(30);
	m_lap.setColor(Color(245, 198, 80));
	m_lap.setPosition(VIEW_SIZE_X - m_lap.getLocalBounds().width, HAND_X);	

	m_finalScreen.setFont(m_font);	
	m_finalScreen.setCharacterSize(30);
	m_finalScreen.setColor(Color(245, 198, 80));
	m_finalScreen.setPosition(300, HAND_Y/2);

	m_bestLapText.setFont(m_font);
	m_bestLapText.setString("Best Lap : 00'00:00");
	m_bestLapText.setCharacterSize(30);
	m_bestLapText.setColor(Color(245, 198, 80));
	m_bestLapText.setPosition(VIEW_SIZE_X - m_bestLapText.getLocalBounds().width + 80, HAND_X + 30);

	m_bestLapText.setFont(m_font);
	m_bestLapText.setString("Best Lap : 00'00:00");
	m_bestLapText.setCharacterSize(30);
	m_bestLapText.setColor(Color(245, 198, 80));
	m_bestLapText.setPosition(VIEW_SIZE_X - m_bestLapText.getLocalBounds().width + 80, HAND_X + 30);

	m_currentTimer.setFont(m_font);
	m_currentTimer.setString("Current : 00'00:00");
	m_currentTimer.setCharacterSize(30);
	m_currentTimer.setColor(Color(245, 198, 80));
	m_currentTimer.setPosition(VIEW_SIZE_X - m_bestLapText.getLocalBounds().width + 90, HAND_X + 60);
	return "";
}

void GraphicEngine::loadSprite()
{
	m_S_speedMeter.setTexture(m_T_speedMeter);
	m_S_speedMeter.setScale(m_speedMeterScale, m_speedMeterScale);
	m_S_speedMeter.setPosition(SPEED_METER_X, SPEED_METER_Y);

	m_S_hand.setTexture(m_T_hand);
	m_S_hand.setScale(m_handScale, m_handScale);
	m_S_hand.setPosition(HAND_X, HAND_Y);
	m_S_hand.setOrigin(57, 716);
	m_S_hand.setRotation(HAND_BEGIN_POSITION);
}

void GraphicEngine::initView()
{
	//Init the View	
	viewMeter.setSize(VIEW_SIZE_X, VIEW_SIZE_Y);
}

void GraphicEngine::initVar()
{
}

void GraphicEngine::newLap()
{
	int lastLap;
	string s = "";
	string m = "";
	string mS = "";
	string chrono = "";
	int milliSeconds;
	int seconds;
	int minutes;

	lastLap = m_chronometer.getTimer() / 10;
	m_chronometer.resetChrono();

	if (m_bestLap == -1 || lastLap < m_bestLap)
	{
		m_bestLap = lastLap;		
		cout << m_bestLap << endl;

		milliSeconds = lastLap % 100;
		lastLap = lastLap / 100;
		seconds = lastLap % 60;
		minutes = lastLap / 60;

		chrono = "Current : ";
		if (minutes < 10)
			m = "0";

		if (seconds < 10)
			s = "0";

		if (milliSeconds < 10)
			mS = "0";

		chrono = "Best Lap : " + m + to_string(minutes) + "'" + s + to_string(seconds) + ":" + mS + to_string(milliSeconds);
		m_bestLapText.setString(chrono);
	}
}

void GraphicEngine::setTextForDraw(float speed, int lap, int maxLap)
{
	ostringstream ss;
	int tmp;
	string tmpLap;
	string chrono = "";
	string s = "";
	string m = "";
	string mS = "";

	int milliSeconds;
	int seconds;
	int minutes;

	m_S_hand.setRotation(speed * SPEED_ADAPTOR + HAND_BEGIN_POSITION);
	tmp = speed*SPEED_ADAPTATOR_TEXT;
	ss << tmp;
	tmpLap = "Lap : " + to_string(lap) + " / " + to_string(maxLap);

	m_speedText.setString(ss.str());
	m_speedText.setPosition(HAND_X - 20, HAND_Y + 10);

	m_lap.setString(tmpLap);
	m_lap.setPosition(VIEW_SIZE_X - m_lap.getLocalBounds().width / 2 , HAND_X);

	tmp = m_chronometer.getTimer() / 10;
	milliSeconds = tmp % 100;
	tmp = tmp / 100;	
	seconds = tmp % 60;
	minutes = tmp / 60;

	chrono = "Current : ";
	if (minutes < 10)
		m = "0";
	
	if (seconds < 10)
		s = "0";

	if (milliSeconds < 10)
		mS = "0";

	chrono = "Current : " + m + to_string(minutes) + "'" + s + to_string(seconds) + ":" + mS + to_string(milliSeconds);
	m_currentTimer.setString(chrono);
}

void GraphicEngine::draw(float speed, int lap, int maxLap)
{
	m_chronometer.getTimer();
	setTextForDraw(speed, lap, maxLap);
	window.setView(viewMeter);		
	window.draw(m_S_speedMeter);			
	window.draw(m_S_hand);
	window.draw(m_lap);
	window.draw(m_speedText);	
	window.draw(m_bestLapText);
	window.draw(m_currentTimer);
}

void GraphicEngine::drawFinalScreen()
{
	string display = "";
	string m;
	string s;
	string mS;

	int minutes;
	int seconds;
	int milliSeconds;	
	int bestLap;

	milliSeconds = m_bestLap % 100;
	bestLap = m_bestLap / 100;
	seconds = bestLap % 60;
	minutes = bestLap / 60;

	display = "Current : ";
	if (minutes < 10)
		m = "0";

	if (seconds < 10)
		s = "0";

	if (milliSeconds < 10)
		mS = "0";

	display = "Thank you for playing to\n\"Lord of the Race\"\n\n";
	display = display + "Your best lap : " + m + to_string(minutes) + "'" + s + to_string(seconds) + ":" + mS + to_string(milliSeconds) +"\n\nPress \"Back\" to exit the game.";


	window.setView(viewMeter);
	m_finalScreen.setString(display);
	window.draw(m_finalScreen);
}