#include"Player.h"

Player::Player() {
	//default settings
	position.x = 0.0f;
	position.y = 0.0f;
	velosity.x = 0.0f;
	velosity.y = 0.0f;
	speed = 200.0f;
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
	velosity.x += dirx * speed;
	return;
}

void Player::update(double deltatime) {
	position.x += velosity.x * deltatime;
	position.y += velosity.y * deltatime;
	velosity.x = 0;
	velosity.y = 0;
	return;
}
void Player::render(sf::RenderWindow& window) {
	sprite.setPosition(position);
	//deals with the current frame of sprite in animation
	window.draw(sprite);
	return;
}

