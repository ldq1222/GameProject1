#pragma once
#include<SFML/Graphics.hpp>
//initialize=ChuShiHua
//init() is better than Player() because it
//can load the Player multiple times 
class Player
{	
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
public:
	Player();
	//auto gets called out when created
	~Player();
	//auto gets called out when deleated
	
	void init(std::string texture_name, sf::Vector2f pos, float gravity);
	void walk(int dir);
	void update(double deltatime);
};



