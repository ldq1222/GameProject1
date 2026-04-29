#pragma once
#include<SFML/Graphics.hpp>
//initialize=ChuShiHua
//init() is better than Player() because it
//can load the Player multiple times 

//Annotation:ZhuShi
class Player
{	
private:
	sf::Sprite sprite;
	sf::Texture texture;
	sf::Vector2f position;
	sf::Vector2f velosity;
	float speed;
public:
	Player();
	//auto gets called out when created
	~Player();
	//auto gets called out when deleated
	
	void init(std::string texture_name, sf::Vector2f pos, float gravity);
	sf::Sprite& getSprite();
	sf::Texture& getTexture();
	void setPosition(sf::Vector2f pos);
	void walk(int dir);
	void update(double deltatime);
	void render(sf::RenderWindow& window);
};



