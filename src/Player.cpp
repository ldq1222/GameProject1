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
const int HEIGHT = 1080, WIDTH = 1920;//this is bad
Player::Player() {
	//default settings
	isJump = 0;
	position.x = 0.0f;
	position.y = 0.0f;
	velocity.x = 0.0f;
	velocity.y = 0.0f;
	speed = 300.0f;
	jumpVel = 1000.0f;
	box.init(position,{100.0f,100.0f});
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
sprite.setPosition({ position.x, 500.0f - position.y });
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

sf::Vector2f Player::getPosition() {
	return position;
}

void Player::setPosition(sf::Vector2f pos) {
	position = pos;
}
sf::Vector2f Player::getVelocity() {
	return velocity;
}

float Player::getHeight() {
	return box.getBox().getSize().y;
}

float Player::getWidth() {
	return box.getBox().getSize().x;
	//super invoke-tion 
}
void Player::setVelocity(sf::Vector2f vel) {
	velocity = vel;
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
void Player::collide(sf::Sprite& obstacle) {//later this pass-by-reference will be removed
	sf::FloatRect a = getSprite().getGlobalBounds();//this is bad
	sf::FloatRect ss = obstacle.getGlobalBounds();
	float aL = a.left, aD = HEIGHT - (a.top + a.height), aU = aD + a.height, aR = aL + a.width;
	float ssL = ss.left, ssD = HEIGHT - (ss.top + ss.height), ssU = ssD + ss.height, ssR = ssL + ss.width;
	if (a.intersects(ss)) {
		std::cout << "collided!\n";
		float lapL = aR - ssL;
		float lapR = ssR - aL;
		float lapU = ssU - aD;
		float lapD = aU - ssD;

		float lapMin = std::min(lapL, std::min(lapR, std::min(lapU, lapD)));
		//GeeX taught me this spagetti code
		//all faults on them
		sf::Vector2f pos =getPosition();
		if (lapMin == lapL) {
			pos.x -= lapL;
		}
		else if (lapMin == lapR) {
			pos.x += lapR;
		}
		else if (lapMin == lapU) {
			pos.y += lapU;
			isJump = 0;
		}
		else if (lapMin == lapD) {
			pos.y -= lapD;
		}
		setPosition(pos);
	}
}
void Player::update(double deltatime, float g,sf::Sprite& obstacle) {
	position.x += velocity.x * deltatime;
	position.y += velocity.y * deltatime;
	velocity.x = 0;
	if (isJump) {
		velocity.y -= g * deltatime;
	}
	//this also enables the thing to fall down from 
	//platforms and stuff.
	//upd:so this is actually a reverse'OnGround', which I have wrote before in some other timeline.
	if (position.y <= 0.0f) {
		position.y = 0.0f;
		velocity.y = 0.0f;
		isJump = 0;
	}
	box.getBox().setPosition(position);
    sprite.setPosition({ position.x, 500.0f - position.y });//see above,this is bad
	collide(obstacle);
	return;
}

void Player::render(sf::RenderWindow& window) {
	sprite.setPosition({ position.x,830.0f - position.y });
	//deals with the current frame of sprite in animation
	window.draw(sprite);
	return;
}
