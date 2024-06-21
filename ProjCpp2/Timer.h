#pragma once

#include"common.h"
#include <string>
#include "Resources.h"




class Timer
{
private:
public: 

	enum TimerState {
		END,COUNTING
	};


	void init()
	{
		font = Assets::getAssets()->font;
		context = Assets::getAssets()->context;
		header.setFont(*(Assets::getAssets()->font));
		header.setCharacterSize(19);
		header.setFillColor(sf::Color::Black);
		header.setStyle(sf::Text::Bold);
		header.setString("Time:");
		time.setFont(*(Assets::getAssets()->font));
		time.setCharacterSize(19);
		time.setFillColor(sf::Color::Black);
		time.setStyle(sf::Text::Bold);
	}
	
	

	void start(int time)
	{
		s = time;
		t1 = clock.restart();
		state = COUNTING;
	}
	TimerState getState()
	{
		return state;
	}
	void update()
	{
		remaining = s - clock.getElapsedTime().asMilliseconds()/1000;
		if (remaining <= 0)
			state = END; 
	}
	
	void render()
	{
		if (remaining < 10)
		{
			header.setFillColor(sf::Color::Red);
			time.setFillColor(sf::Color::Red); 
		}
		else {
			header.setFillColor(sf::Color::Black);
			time.setFillColor(sf::Color::Black);
		}
	
		float x = 200;
		header.setPosition(x, 5);
		time.setPosition({ header.getLocalBounds().width + x + 5,5 }); 
		time.setString(std::to_string(remaining).c_str());
		context->draw(header);
		if (state == TimerState::COUNTING) 
		context->draw(time); 
		

		
		
		
	}

private:
	sf::RenderTarget* context;
	sf::Clock clock; 
	sf::Time t1;
	sf::Font* font;
	sf::Text header;
	sf::Text time; 
	int s;
	int remaining; 
	TimerState state;


};

