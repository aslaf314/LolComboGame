#pragma once

#include "common.h"
#include "Resources.h"
#include <string>


using namespace sf; 
class Counter
{
public: 
	void render()
	{
		RenderTarget* context = Assets::getAssets()->context;
		header.setPosition({ 5,5 }); 
		context->draw(header);
		auto r = header.getGlobalBounds();
		score.setPosition({ r.getPosition().x + r.getSize().x + 5 },5); 
		context->draw(score); 



	}

	int getScore()
	{
		return points; 
	}

	void add(int val)
	{
		points+=val;
		score.setString(std::to_string(points)); 
		
	}

	void init()
	{
		points = 0; 
		header.setFont(*(Assets::getAssets()->font)); 
		header.setCharacterSize(19);
		header.setFillColor(Color::Black);
		header.setStyle(Text::Bold);
		header.setString("Score:"); 
		score.setCharacterSize(19);
		score.setFont(*(Assets::getAssets()->font)); 
		score.setStyle(Text::Bold);
		score.setFillColor(Color::Black);
		add(0); 

	}

private: 
	Text header;
	Text score;
	int points; 

};

