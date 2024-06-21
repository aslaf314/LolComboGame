#pragma once
#include "common.h"
#include <random>
#include "Resources.h"
#include "MousePanel.h"
#define TILE_SIZE 60


#define MAX_COMBO_LENGTH 6




struct Tile
{
	enum State {
		NEUTRAL, GOOD, WRONG
	};

	enum Action
	{
		Q = 0, W = 1, E = 2, R = 3, D = 4, F = 5, A = 6, CLICK = 7
	};



	State state;
	Action action; 


	inline static  const char* ActionToString(Action a)
	{
		switch (a)
		{
		case Q:
			return "Q";
		case W:
			return "W";
		case E:
			return "E";
		case R:
			return "R";
		case D:
			return "D";
		case F:
			return "F";
		case A:
			return "A";
		case CLICK:
			return "MB";
		}
	}

	inline static  sf::Keyboard::Key ActionToEvent(Action a)
	{
		switch (a)
		{
		case Q:
			return sf::Keyboard::Q;
		case W:
			return sf::Keyboard::W;
		case E:
			return sf::Keyboard::E;
		case R:
			return sf::Keyboard::R;
		case D:
			return sf::Keyboard::D;
		case F:
			return sf::Keyboard::F;
		case A:
			return sf::Keyboard::A;
	
		}
	}

	Tile(Action a)
	{
		action = a;
		state = NEUTRAL;
	}


	

};

class Combo
{

public:
	enum ComboState
	{
		ACTIVE,WIN, LOST
	};
public: 
	std::vector<Tile> combo;
	int length;
	int index;
	static std::mt19937 rand;
	static  std::uniform_int_distribution<std::mt19937::result_type> combo_length_dist;
	static std::uniform_int_distribution<std::mt19937::result_type> combo_dist;
	ComboState state; 
	MousePanel* panel;
	
private:
	void generate()
	{
		bool mouse = false;
		length = combo_length_dist(rand); 
		for (int i = 0; i < length; i++)
		{
			
			int random = combo_dist(rand); 
			combo.push_back(Tile(static_cast<Tile::Action>(random))); 
			if (random == Tile::Action::CLICK)
			{
				mouse = true; 
			}
		
		}

		if (!mouse)
		{
			combo[0] = Tile(Tile::Action::CLICK);
		}
	}
public:

	Combo()
	{

		index = 0;
		state = ACTIVE; 
		generate();

	}

	const Tile& operator[](int i)
	{
		if (i < length)
			return combo[i]; 
	}

	

	

	void check()
	{
		if (index >= length)return;
		if (combo[index].action == Tile::Action::CLICK)
		{
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && panel->hit() )
			{
				combo[index].state = Tile::GOOD;
				if (index == (length - 1))
					state = WIN;
				
			}
			else {
				combo[index].state = Tile::WRONG;
				state = LOST;
			}
			index++;
			panel->click();
			return; 
		}
		if (sf::Keyboard::isKeyPressed(Tile::ActionToEvent(combo[index].action)))
		{
			combo[index].state = Tile::GOOD;
			if (index == (length - 1))
				state = WIN;
		}
		else {
			combo[index].state = Tile::WRONG;
			state = LOST; 

		}
		panel->click();
		index++;
	}

};



class ComboPanel
{
public:
	enum PanelState
	{
			ACTIVE, 
			WIN, 
			LOST,
			END
	};
private:
	Combo* combo;
	PanelState state;
private:
	void renderTile(const Tile& a,float x ,float y)
	{
		sf::Color color;
		switch (a.state)
		{
		case Tile::NEUTRAL:
			color = sf::Color::Black; 
			break;
		case Tile::GOOD:
			color = sf::Color(25, 230, 32);
			break;
		case Tile::WRONG:
			color = sf::Color::Red;
		}
		const char* string = Tile::ActionToString(a.action); 
		sf::RectangleShape rectangle({ TILE_SIZE,TILE_SIZE }); 
		rectangle.setOutlineColor(color); 
		rectangle.setOutlineThickness(4); 
		rectangle.setPosition({ x,y }); 
		context->draw(rectangle); 
		sf::Text text;
		text.setFont(*font); 
		text.setStyle(sf::Text::Bold);
		text.setCharacterSize(49);
		text.setFillColor(color);
		text.setString(string);
		text.setOrigin(text.getGlobalBounds().getSize() / 2.f + text.getLocalBounds().getPosition());
		text.setPosition(rectangle.getPosition() + (rectangle.getSize() / 2.f));
		context->draw(text); 
		
	}

	

public: 
	ComboPanel()
	{
		font = Assets::getAssets()->font;
		context = Assets::getAssets()->context;
		ok.setFont(*font);
		ok.setStyle(sf::Text::Bold);
		ok.setCharacterSize(55);
	
	}

	void init(MousePanel* p)
	{
		panel = p;

		combo = new Combo();
		combo->panel = p;
		state = ACTIVE;
	}

	void regenerate()
	{
		delete combo; 
		combo = new Combo();
		combo->panel = panel;

		state = ACTIVE; 
		win = false;
	}

	

	void activate()
	{
		if (state == ACTIVE) {
			listening = true;
		}
	}

	PanelState getState()
	{
		return state;
	}

	void update()
	{
		//std::cout << state<<"\n";
		switch (state)
		{
		case ACTIVE:
			if (listening)
			{
				combo->check();
				listening = false;
			}
			if (combo->state == Combo::WIN)
			{
				state = WIN;
			}
			if (combo->state == Combo::LOST)
			{
				state = LOST; 
			}
			break;
		case WIN: 
			state = END;
			win = true; 
			break;
		case LOST:
			state = END; 
			win = false; 
			break; 
		}

	} 

	void render()
	{
		
			float x = TILE_SIZE / 2;
			float y = 60;
			for (int i = 0; i < combo->length; i++)
			{
				if(state == ACTIVE && i == combo->index)
					renderTile((*combo)[i], x, y-10);
				else
					renderTile((*combo)[i], x, y);
				x += TILE_SIZE + 10;
			}

			if (state == END)
			{
				if (win)
				{
					ok.setPosition(x + 20, y-4);
					ok.setString(":)");
					ok.setFillColor(sf::Color(25, 230, 32));
					context->draw(ok);
				}
				else {
					ok.setPosition(x + 20, y-4);
					ok.setFillColor(sf::Color::Red);
					ok.setString(":|");
					context->draw(ok); 
				}
			}
			

			
		

	}
	
private:
	sf::RenderTarget* context; 
	sf::Font* font; 
	bool listening = false; 
	bool win = false; 
	sf::Text ok;
	MousePanel* panel;
	
	
	
};

