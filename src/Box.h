#pragma once
#include<SFML/Graphics.hpp>

class Box
{
private:
	sf::RectangleShape box;
public:
	Box();
	~Box();
	void init(sf::Vector2f leftop, sf::Vector2f size);
	sf::RectangleShape getBox();
//	void setPos(sf::Vector2f pos);
	//AI adviced to remove this and put the logic 
	//in the Player
};

