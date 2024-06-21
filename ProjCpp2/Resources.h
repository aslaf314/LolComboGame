#pragma once
#include "common.h"

class Assets
{
public:
	sf::Font* font;
	sf::RenderWindow* context; 
	
	static Assets* getAssets(); 

private:
	static Assets* src;


};
