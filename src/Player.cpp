#include"Player.h"

Player::Player() {
	//default settings
	position.x = 0.0f;
	position.y = 0.0f;
}

Player::~Player() {
	//empty&release (?) &save data
	//sfml can auto clear Sprites
}
void Player::init(std::string texture_name, sf::Vector2f pos, float g) {
	position = pos;
	texture.loadFromFile(texture_name);
//	sprite.setTexture();
	sprite.setPosition(position);
}
void Player::walk(int dir) {
	
}

void Player::update(double deltatime) {
	
}

