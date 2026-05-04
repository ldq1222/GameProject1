#include"Player.h"
#include<nlohmann/json.hpp>
#include<fstream>
#include<iostream>
using json = nlohmann::json;
//NOTICE:
//the json does not allow annos after all,though
//the editor wont warn about this.
//Anno from player.json:
//'it seems to be double'
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
void Player::init(std::string texture_name, float g) {
	std::ifstream playerFile("src/player.json", std::ios::binary);
	if (!playerFile.is_open()) {
		std::cout << "failed to open player.json\n";
	}
	json playerData;
	playerFile >> playerData;
	//I hate adding an error log in these places.
	//I cannot understand why you have to write the key and value both in this func...
	//above means the value() function of json
	position.x = playerData["position"]["x"];
	position.y = playerData["position"]["y"];
	texture.loadFromFile(texture_name);
	sprite.setTexture(texture);
	sprite.setPosition(position);
	return;
}
void Player::saveData(const std::string& filePath)const {
	//second const means it doesnt change the state of player
	json playerData;
	playerData["position"]["x"] = position.x;
	if (!isJump)playerData["position"]["y"] = position.y;
	else playerData["position"]["y"] = 0.0f;
	//////of course this needs to be fixed later
	std::ofstream playerFile(filePath, std::ios::binary);
	if (!playerFile.is_open()) {
		std::cout << "failed to open playerFile and save\n";
	}
	playerFile << playerData.dump(4);
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

void Player::update(double deltatime, float g) {
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
	sprite.setPosition({ position.x,500.0f - position.y });
	//deals with the current frame of sprite in animation
	window.draw(sprite);
	return;
}
