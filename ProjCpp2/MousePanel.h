#pragma once
#include "common.h"
#include "Resources.h"
#include <random>
using namespace sf; 


#define MP_SIZE 200

class MousePanel
{


public :
	void init()
	{
		ctx = Assets::getAssets()->context;
		xPoint = coordsX(rand);
		yPoint = coordsY(rand); 
		rect.setPosition({ ctx->getSize().x - MP_SIZE - 10.0f, ctx->getSize().y - MP_SIZE - 10.0f });
		rect.setSize({ MP_SIZE, MP_SIZE });
		c.restart();

	}

	void click()
	{
		xPoint = coordsX(rand);
		yPoint = coordsY(rand);
		
	}

	void update()
	{
		
	}

	bool hit()
	{
		if (Mouse::isButtonPressed(Mouse::Left))
		{
			int x = Mouse::getPosition(*ctx).x;
			int y = Mouse::getPosition(*ctx).y;
			x = x - rect.getPosition().x-6;
			y = y - rect.getPosition().y+2; 
			int dist2 = (x - xPoint) * (x - xPoint) + (y - yPoint) * (y - yPoint);
			
			if (dist2 <= 200) {
				return true;
			}

		}
		return false;
	}

	void render()
	{
		rect.setOutlineColor(Color::Black); 
		rect.setOutlineThickness(3); 
		ctx->draw(rect); 
		CircleShape cs;

		cs.setFillColor(Color::Blue);
		cs.setPosition({ xPoint + rect.getPosition().x-5, (float)yPoint + rect.getPosition().y-5});
		cs.setRadius(10);
		ctx->draw(cs); 

			
	}
private:
	Clock c; 
	Clock c2;
	static std::mt19937 rand;
	int xPoint, yPoint;
	static std::uniform_int_distribution<std::mt19937::result_type> coordsX;
	static std::uniform_int_distribution<std::mt19937::result_type> coordsY;
	RectangleShape rect;
	RenderWindow* ctx;
	CircleShape cs;

	


};

