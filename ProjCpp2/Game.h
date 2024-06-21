#pragma once
#include "common.h"
#include <iostream>
#include "Timer.h"
#include "ComboPanel.h"
#include "Resources.h"
#include "Counter.h"
#include "MousePanel.h"
using namespace sf; 


class Game
{
private:

public:
	enum GameState
	{
		GAME, END, INIT, MENU
	};

	GameState state;

	Game() 
	{
	}

	void init()
	{
		window = new RenderWindow(VideoMode(750, 320), "LOL COMBO CHALANGE");
		window->setKeyRepeatEnabled(false); 
		window->setFramerateLimit(256); 

		if (!font.loadFromFile("font3.ttf"))
		{
			std::cout << "Could not find font"; 
		}
		font.setSmooth(false);

		assets = Assets::getAssets();
		assets->context = window;
		assets->font = &font; 
	
	}

	void initGameComponents()
	{
		panel = new ComboPanel();
		points = new Counter();
		timer = new Timer();
		mpanel = new MousePanel(); 
		timer->init();
		points->init();
		mpanel->init();
		panel->init(mpanel);

		
		timer->start(60);
		state = GAME;
	}

	void disposeGameComponents()
	{
		std::cout << "disposing\n";
		delete panel;
		delete points;
		delete timer;
		delete mpanel; 
	}


	void run()
	{
		state = INIT;
		while (window->isOpen())
		{
			
			pollEvents(); 
			update();
			render();
	

		}
	}

	void pollEvents()
	{
		Event ev; 
		window->pollEvent(ev);
		if (ev.type == Event::Closed)
		{
			window->close();
			exit(0); 
		}
		if (state == INIT)return;
		if (state == MENU)
		{
			if (ev.type == Event::KeyPressed)
				if (Keyboard::isKeyPressed(Keyboard::Enter))
					state = INIT; 
		}
		if (ev.type == Event::KeyPressed)
		{
			panel->activate();
		}
		if (ev.type == Event::MouseButtonPressed)
		{
			panel->activate();
		}
		
	}

	void update()
	{
		switch (state) {
		case INIT: 
			initGameComponents();
			break;
		case GAME:
			updateTimer();
			updatePanel();
			updateClickPanel();
			break;
		case END:
			score = points->getScore();
			disposeGameComponents();
			state = MENU; 
			break;
		case MENU:
			break; 
		}
		
	}
	Clock  panel_wait_t;
	void updatePanel()
	{
		panel->update();
		if (panel->getState() == ComboPanel::WIN)
		{
			points->add(1); 
		}
		if (panel->getState() == ComboPanel::WIN || panel->getState() == ComboPanel::LOST)
		{
			panel_wait_t.restart();
			//std::cout << "restart()\n"; 
		}

		if (panel->getState() == ComboPanel::END)
		{
			if (panel_wait_t.getElapsedTime().asSeconds() > 0.6)
				panel->regenerate();
		}
	}
	void updateTimer()
	{
		timer->update();
		if (timer->getState() == Timer::TimerState::END)
		{
			state = END;
		}
	}

	void updateClickPanel()
	{
		mpanel->update();
	}

	void renderMenu()
	{
		Text result;
		result.setCharacterSize(50);
		result.setFillColor(sf::Color::Black);
		result.setFont(font); 
		result.setStyle(sf::Text::Bold);
		std::string t = "SCORE: ";
		t += std::to_string(score); 
		result.setString(t.c_str());
		result.setPosition({ (window->getSize().x - result.getLocalBounds().width) / 2, 70 });
		window->draw(result); 
	}

	void render()
	{
		window->clear(Color(200,200,200));
		if (state == GAME) {
			panel->render();
			points->render();
			timer->render();
			mpanel->render();
		}
		else if(state == MENU) {
			renderMenu();
		}
		window->display(); 
	}

private:
	RenderWindow* window;
	Timer* timer;
	Font font; 
	ComboPanel* panel; 
	Assets* assets; 
	Counter* points;
	MousePanel* mpanel; 
	int score = 0;
	
	
};

