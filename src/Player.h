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
	const float speedCommon = 10.0f;
	const float speedJump = 2.0f;
	const float speedDash = 100.0f;
	const float speedClimb = 5.0f;
	const float weight = 20.0f;
	const double lengthCanDash = 40.0f;
	int directionX;
	int directionY;
	sf::Vector2f speedCurrent;
	bool isDashing;
	bool isJumping;
	bool isWalking;
	bool isFalling;
	int countJump;
	double lengthDash;
public:
	Player();
	//auto gets called out when created
	~Player();
	//auto gets called out when deleated
	
	void init(std::string texture_name, sf::Vector2f pos, float gravity);
<<<<<<< Updated upstream
	
	void walk(int dir);
	void climb(int dir);
	void fall();
	void dash(int dir);
	void jump();
=======
	void walk();
>>>>>>> Stashed changes
	void update(double deltatime);
	sf::Sprite getSprite();
};



