#include"Player.h"

Player::Player() {
	//default settings
	isJump = 0;
	position.x = 0.0f;
	position.y = 0.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	speed = 200.0f;
	jumpVel = 700.0f;
}

Player::~Player() {
	//empty&release (?) &save data
	//sfml can auto clear Sprites
}
void Player::init(std::string texture_name, sf::Vector2f pos, float g) {
	position = pos;
	texture.loadFromFile(texture_name);
	sprite.setTexture(texture);
	sprite.setPosition(position);
	return;
}
sf::Sprite& Player::getSprite() {
	return sprite;
}
sf::Texture& Player::getTexture() {
	return texture;
}
void Player::setPosition(sf::Vector2f pos) {
	position = pos;
}
void Player::walk(int dirx) {
	velocity.x += dirx * speed;
	return;
}
void Player::jump(int g) {
	if (isJump == 0) {
		isJump = 1;
		velocity.y = jumpVel;
	}
	return;
}
void Player::update(double deltatime,float g) {
	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;
	velocity.x = 0;
	if (isJump) {
		velocity.y -= g * deltatime;
	}
	if (position.y <= 0.0f) {
		position.y = 0.0f;
		velocity.y = 0.0f;
		isJump = 0;
	}
	
	return;
}
void Player::render(sf::RenderWindow& window) {
	sprite.setPosition({position.x,500.0f-position.y});
	//deals with the current frame of sprite in animation
	window.draw(sprite);
	return;
}

